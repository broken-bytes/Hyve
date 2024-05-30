#include "parser/HParser.hxx"
#include "parser/HParserError.hxx"
#include "parser/nodes/HAstBinaryExpressionNode.hxx"
#include "parser/nodes/HAstUnaryExpressionNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include "parser/nodes/HAstReturnNode.hxx"
#include "parser/nodes/HAstFileNode.hxx"
#include "parser/nodes/HAstModuleDeclNode.hxx"
#include "parser/nodes/HAstFuncCallNode.hxx"
#include "parser/nodes/HAstFuncDeclNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstArrayNode.hxx"
#include "parser/nodes/HAstFuncBodyNode.hxx"
#include "parser/nodes/HAstMemberAccessNode.hxx"
#include "parser/nodes/HAstVarDeclNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/nodes/HAstPropAccessNode.hxx"
#include "parser/nodes/HAstLiteralNode.hxx"
#include "parser/nodes/HAstClassNode.hxx"
#include "parser/nodes/HAstClassBodyNode.hxx"
#include "parser/nodes/HAstPrototypeNode.hxx"
#include "parser/nodes/HAstPrototypeBodyNode.hxx"
#include "parser/nodes/HAstProtocolNode.hxx"
#include "parser/nodes/HAstProtocolBodyNode.hxx"
#include "parser/nodes/HAstStructNode.hxx"
#include "parser/nodes/HAstStructBodyNode.hxx"
#include "parser/nodes/HAstInitNode.hxx"
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <core/HAccessLevel.hxx>

#include <sstream>

namespace Hyve::Parser {
    HParser::HParser() : _tokenIndex(0) {

    }

    std::shared_ptr<HAstNode> HParser::Parse(std::string fileName, std::vector<Lexer::HToken>& tokens) {
        _tokens = tokens;

        auto ast = std::make_shared<HAstFileNode>();
        ast->Name = fileName;
        ast->Type = HAstNodeType::File;
        auto token = ParseNextNonLN();
        token = Peek();

        Core::HAccessLevel accessLevel = Core::HAccessLevel::Internal;

        while(token.Type != Lexer::HTokenType::END_OF_FILE) {
            switch (token.Family) {
                case Lexer::HTokenFamily::KEYWORD: {
                    switch(token.Type) {
                        case Lexer::HTokenType::PUBLIC:
                            accessLevel = Core::HAccessLevel::Public;
                            // Consume the access level token
                            token = Consume();
							break;
                        case Lexer::HTokenType::PRIVATE:
                            accessLevel = Core::HAccessLevel::Private;
                            // Consume the access level token
                            token = Consume();
                        case Lexer::HTokenType::INTERNAL:
                            accessLevel = Core::HAccessLevel::Internal;
                            // Consume the access level token
                            token = Consume();
                        case Lexer::HTokenType::MODULE: {
							ast->Children.push_back(ParseModuleDecl());
							break;
						}
                        case Lexer::HTokenType::PROTOTYPE: {
                            ast->Children.push_back(ParsePrototypeDecl(accessLevel));
                            break;
                        }
                        case Lexer::HTokenType::PROTOCOL: {
                            ast->Children.push_back(ParseProtocolDecl(accessLevel));
                            break;
                        }
                        case Lexer::HTokenType::STRUCT: {
                            ast->Children.push_back(ParseStructDecl(accessLevel));
                            break;
                        }
                        case Lexer::HTokenType::CLASS: {
                            ast->Children.push_back(ParseClassDecl(accessLevel));
                            break;
                        }
                        case Lexer::HTokenType::FUNC: {
                            ast->Children.push_back(ParseFuncDecl(accessLevel));
                            break;
                        }
                        case Lexer::HTokenType::VAR:
                            ast->Children.push_back(ParseVarDecl(accessLevel, true));
                            break;
                        case Lexer::HTokenType::LET: {
                            ast->Children.push_back(ParseVarDecl(accessLevel, false));
                            break;
                        }
                        default:
                            throw HParserError("Unexpected keyword");
                    }

                    token = ParseNextNonLN();
                    token = Peek();
                    break;
                }
							 
                default:
                    throw HParserError("Expecting a top level declaration");
            }
        }

        return ast;
    }

    bool HParser::CanStartStatement() {
        auto token = Peek();

        switch(token.Type) {
            case Lexer::HTokenType::RETURN:
            case Lexer::HTokenType::VAR:
            case Lexer::HTokenType::LET:
            case Lexer::HTokenType::IDENTIFIER:
            case Lexer::HTokenType::SELF:
                return true;
            default:
                return false;
        }
    }

    bool HParser::CanStartExpression() {
        auto token = Peek();

        switch(token.Type) {
            case Lexer::HTokenType::IDENTIFIER:
            case Lexer::HTokenType::STRING:
            case Lexer::HTokenType::TRUE:
            case Lexer::HTokenType::FALSE:
            case Lexer::HTokenType::NULL_LITERAL:
            case Lexer::HTokenType::NUM:
                return true;
            default:
                return false;
        }
    }

    std::shared_ptr<HAstVarDeclNode> HParser::ParseVarDecl(Core::HAccessLevel accessLevel, bool isMutable) {
        auto ast = std::make_shared<HAstVarDeclNode>();
        ast->IsMutable = isMutable;

        // Ensure we have a var keyword. Let will be introduced later
        auto token = Consume(Lexer::HTokenType::VAR, "Expected var keyword to start variable declaration");

        token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after variable declaration");
        ast->Name = token.Value;

        if(Peek().Type == Lexer::HTokenType::COLON) {
            token = Consume();
            ast->TypeNode = ParseType();
        }
        // Check if we have an assignment
        if(Peek().Type == Lexer::HTokenType::ASSIGNMENT) {
            // Parse the expression
            // Consume the assignment token, so we can parse the expression on its own
            token = Consume();
            ast->Initializer = ParseExpression();
        }

        token = Peek();

        return ast;
    }

    std::shared_ptr<HAstReturnNode> HParser::ParseReturnStatement() {
        auto ast = std::make_shared<HAstReturnNode>();

        auto token = Consume();

        while(true) {
            if(token.Type == Lexer::HTokenType::LINEBREAK) {
                token = Consume();
                continue;
            } else if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in return statement");
            } else {
                break;
            }
        }

        if(CanStartExpression()) {
            ast->Children.push_back(ParseExpression());
        }

        return ast;
    }

    std::shared_ptr<HAstNode> HParser::ParseFuncDecl(Core::HAccessLevel accessLevel) {
        // Func Root
        auto ast = std::make_shared<HAstFuncDeclNode>();
        ast->Children = {};

        // Func keyword
        auto token = Consume(Lexer::HTokenType::FUNC, "Expected func keyword to start function declaration");

        // Func must be followed by an identifier
        token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after function declaration");
        ast->Name = token.Value;

        // Check for parameters. If the second next token is an identifier, then we have parameters
        if(Peek().Type == Lexer::HTokenType::LBRACKET) {
            ast->Parameters = ParseParameters();
        }

        // Check for return type. If the next token is an arrow, then we have a return type
        if(Peek().Type == Lexer::HTokenType::ARROW) {
            // Increment index by 1 to skip arrow
            token = Consume(Lexer::HTokenType::ARROW, "Expected arrow in function declaration");
            token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected return type after arrow in function declaration");
            ast->ReturnType = token.Value;
        } else {
            ast->InferReturnType = true;
        }

        // Check for function body. If the next token is a left curly bracket, then we have a function body
        if(Peek().Type == Lexer::HTokenType::LCBRACKET) {
            ast->Children.push_back(ParseFuncBody());
        }

        return ast;
    }

    std::shared_ptr<HAstNode> HParser::ParseInitDecl() {
        auto node = std::make_shared<HAstInitDeclNode>();
        auto token = ParseNextNonLN();

        // Ensure we have an init keyword
        token = Consume(Lexer::HTokenType::INIT, "Expected init keyword to start init block");
        
        _contextStack.push(HParserContext::Function);

        token = ParseNextNonLN();

        // We must check if the init block has any parameters. If it does, then we must parse them
        if(token.Type == Lexer::HTokenType::LBRACKET) {
            node->Parameters = ParseParameters();
        }

        token = ParseNextNonLN();

        node->Children.push_back(ParseFuncBody());

        _contextStack.pop();

        return node;
    }

    std::shared_ptr<HAstFuncBodyNode> HParser::ParseFuncBody() {
        // Func Body Root
        auto ast = std::make_shared<HAstFuncBodyNode>();

        // Make sure we have a left curly bracket
        auto token = Consume(Lexer::HTokenType::LCBRACKET, "Expected left curly bracket after function declaration");

        // Remove all additional linebreaks
        token = ParseNextNonLN();
        // Look ahead 2 tokens
        auto tokens = Peek(2);

        // Go on until we hit a right curly bracket
        while(token.Type != Lexer::HTokenType::RCBRACKET) {
            if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in function body");
            }
            // Statements usually start with a keyword
            else if(token.Family == Lexer::HTokenFamily::KEYWORD) {
                if(token.Type == Lexer::HTokenType::RETURN) {
                    ast->Children.push_back(ParseReturnStatement());
                } else if(token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                    ast->Children.push_back(ParseVarDecl(Core::HAccessLevel::Internal, token.Type == Lexer::HTokenType::VAR));
                } else if(token.Type == Lexer::HTokenType::SELF) {
                    // We need to check if we have an expression or a statement
                    if(
                        tokens[1].Type == Lexer::HTokenType::ASSIGNMENT 
                        || tokens[1].Type == Lexer::HTokenType::PLUS_ASSIGN
                        || tokens[1].Type == Lexer::HTokenType::MINUS_ASSIGN 
                        || tokens[1].Type == Lexer::HTokenType::MULTIPLY_ASSIGN 
                        || tokens[1].Type == Lexer::HTokenType::DIVIDE_ASSIGN
                    ) {
                        ast->Children.push_back(ParseStatement(Core::HAccessLevel::Internal));
                    } else if(tokens[1].Type == Lexer::HTokenType::DOT) {
                        ParseExpression();
                    } else {
                        ast->Children.push_back(ParseStatement(Core::HAccessLevel::Internal));
                    }
                    ast->Children.push_back(ParseExpression());
                } else {
                    throw HParserError("Unexpected keyword in function body");
                }
            }
            // Expression
            else {
                ast->Children.push_back(ParseExpression());
            }

            token = Peek();
        }

        // Make sure we have a right curly bracket
        token = Consume(Lexer::HTokenType::RCBRACKET, "Expected right curly bracket after function body");

        return ast;
    }

    std::shared_ptr<HAstFuncCallNode> HParser::ParseFuncCall() {
        // Don't specify the type to consume, as we may have init or func calls
        auto token = Consume();

        auto ast = std::make_shared<HAstFuncCallNode>();
        ast->Name = token.Value;

        // Ensure we have a left bracket
        token = Consume(Lexer::HTokenType::LBRACKET, "Expected left bracket after function call");

        token = Peek();

        while(token.Type != Lexer::HTokenType::RBRACKET) {
            if(token.Type == Lexer::HTokenType::COMMA) {
                // Increment index by 1 to skip comma
                token = Consume();
            }

            token = Consume(Lexer::HTokenFamily::IDENTIFIER, "Expected identifier in function call");
            ast->Parameters.push_back(HAstCallParamater {
                    .Name = token.Value,
                    .Value = nullptr
                });

            token = Consume(Lexer::HTokenType::COLON, "Expected colon after parameter name");
            ast->Parameters.back().Value = ParseExpression();
            token = Peek();
        }

        token = Consume(Lexer::HTokenType::RBRACKET, "Expected right bracket after parameter declaration");

        return ast;
    }

    std::shared_ptr<HAstPropAccessNode> HParser::ParsePropAccess() {
        auto ast = std::make_shared<HAstPropAccessNode>();

        auto token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier in property access");

        ast->Name = token.Value;

        return ast;
    }

    std::vector<HAstParamater> HParser::ParseParameters() {
        auto parameters = std::vector<HAstParamater>();

        auto token = Consume(Lexer::HTokenType::LBRACKET, "Expected left bracket after parameter declaration");

        token = Peek();

        while(token.Type != Lexer::HTokenType::RBRACKET) {
            if(token.Type == Lexer::HTokenType::COMMA) {
                // Increment index by 1 to skip comma
                token = Consume();
            }

            // Get the identifier
            token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier in parameter declaration");
            parameters.push_back(HAstParamater {
                .Name = token.Value,
                .Type = nullptr
            });
            // Get the colon
            token = Consume(Lexer::HTokenType::COLON, "Expected colon after parameter name");
            // Get the type
            parameters.back().Type = ParseType();

            token = Peek();
        }

        token = Consume(Lexer::HTokenType::RBRACKET, "Expected right bracket after parameter declaration");

        return parameters;
    }

    std::shared_ptr<HAstTypeNode> HParser::ParseType(std::shared_ptr<HAstTypeNode> parent) {
        auto token = Consume();

        // We expect an identifier -> Regular type
        if(token.Type == Lexer::HTokenType::IDENTIFIER) {
            auto type = std::make_shared<HAstTypeNode>();
            type->Name = token.Value;

            if(parent != nullptr) {
                if(Peek().Type == Lexer::HTokenType::RSBRACKET && parent->Name == "Array") {
                    Consume();
                    std::shared_ptr<HAstArrayNode> array = dynamic_pointer_cast<HAstArrayNode>(parent);
                    array->Type = type;
                    type = array;
                } else {
                    throw HParserError("Unexpected type");
                }
            }

            return type;
        }
        // We expect an open bracket -> Array type
        else if(token.Type == Lexer::HTokenType::LSBRACKET) {
            auto array = std::make_shared<HAstArrayNode>();
            array->Name = "Array";
            array->Type = ParseType(array);
            return array;
        } else {
            throw HParserError("Unexpected type");
        }
     }

    std::shared_ptr<HAstNode> HParser::ParseClassDecl(Core::HAccessLevel accessLevel) {
        auto node = std::make_shared<HAstClassNode>();

        // Ensure we have a class keyword
        auto token = Consume(Lexer::HTokenType::CLASS, "Expected class keyword to start class declaration");

        token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after class declaration");
        node->Name = token.Value;

        _contextStack.push(HParserContext::Class);

        if(Peek().Type == Lexer::HTokenType::COLON) {
            node->Inheritance = ParseInheritanceList();
        }

        token = Consume(Lexer::HTokenType::LCBRACKET, "Expected left curly bracket after class declaration");

        auto body = std::make_shared<HAstClassBodyNode>();
        node->Children.push_back(body);

        Core::HAccessLevel currentAccessLevel = Core::HAccessLevel::Internal;

        token = ParseNextNonLN();

        while(token.Type != Lexer::HTokenType::RCBRACKET) {
            if (token.Type == Lexer::HTokenType::PUBLIC) {
				currentAccessLevel = Core::HAccessLevel::Public;
				token = Consume();
			} else if(token.Type == Lexer::HTokenType::PRIVATE) {
				currentAccessLevel = Core::HAccessLevel::Private;
				token = Consume();
            } else if (token.Type == Lexer::HTokenType::INTERNAL) {
                currentAccessLevel = Core::HAccessLevel::Internal;
                token = Consume();
            } else if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in class body");
            } else if(token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                body->Children.push_back(ParseVarDecl(currentAccessLevel, token.Type == Lexer::HTokenType::VAR));
            } else if(token.Type == Lexer::HTokenType::FUNC) {
                body->Children.push_back(ParseFuncDecl(currentAccessLevel));
            } else if (token.Type == Lexer::HTokenType::INIT) {
                body->Children.push_back(ParseInitDecl());
            } else {
                throw HParserError("Unexpected token in class body");
            }

            token = ParseNextNonLN();
        }

        token = Consume(Lexer::HTokenType::RCBRACKET, "Expected right curly bracket after class body");

        _contextStack.pop();

        return node;
    }

    std::shared_ptr<HAstInheritanceNode> HParser::ParseInheritanceList() {
        auto node = std::make_shared<HAstInheritanceNode>();

        auto token = Consume(Lexer::HTokenType::COLON, "Expected colon after class name");

        token = ParseNextNonLN();

        while(token.Type != Lexer::HTokenType::LCBRACKET) {
            if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in inheritance list");
            } else if(token.Type == Lexer::HTokenType::IDENTIFIER) {
                token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier in inheritance list");
                node->InheritedTypes.push_back(token.Value);
                if(Peek().Type == Lexer::HTokenType::COMMA) {
                    token = Consume();
                }
            } else {
                throw HParserError("Unexpected token in inheritance list");
            }

            token = Peek();
        }

        return node;
    }

    std::shared_ptr<HAstExpressionNode> HParser::ParseExpression() {
        return ParseExpressionWithPrecedence(0);
    }

    std::shared_ptr<HAstExpressionNode> HParser::ParseExpressionWithPrecedence(int precedence) {
        auto node = ParseAtomicExpression();

        while (true) {
            auto token = ParseNextNonLN();

            // Check if we have an operator, else we break
            if (token.Family != Lexer::HTokenFamily::OPERATOR) {
                break;
            }

            auto op = ParseOperator();

            // Check if the operator has a precedence higher than the current one
            if(GetOperatorPrecedence(op) < precedence) {
                break;
            }

            auto currentPrecedence = GetOperatorPrecedence(op);

            if (currentPrecedence < precedence) {
                break;
            }

            // Consume the operator
            token = Consume();

            // Parse the RHS of the expression
            auto rhs = ParseExpressionWithPrecedence(currentPrecedence + 1);

            // Build the binary expression
            node = std::make_shared<HAstBinaryExpressionNode>();
            auto binaryNode = std::dynamic_pointer_cast<HAstBinaryExpressionNode>(node);
            binaryNode->LHS = node;
            binaryNode->RHS = rhs;
            binaryNode->Operator = HAstBinaryOperator { op };
        }

        return node;
    }

    std::shared_ptr<HAstExpressionNode> HParser::ParseAtomicExpression() {
        auto token = ParseNextNonLN(); // Peek the next token

        std::shared_ptr<HAstExpressionNode> node;

        switch (token.Type) {
            case Lexer::HTokenType::IDENTIFIER:
                // Handle identifiers (variables, function calls, etc.)
                if(Peek(2)[1].Type == Lexer::HTokenType::DOT) {
                    node = ParseMemberAccess();
                } else if(Peek(2)[1].Type == Lexer::HTokenType::LBRACKET) {
                    node = ParseFuncCall();
                } else {
                    node = ParsePropAccess();
                }
                break;
            case Lexer::HTokenType::SELF:
                // Handle identifiers (variables, function calls, etc.)
                if(Peek(2)[1].Type == Lexer::HTokenType::DOT) {
                    node = ParseMemberAccess();
                } else if(Peek().Type == Lexer::HTokenType::LBRACKET) {
                    node = ParseFuncCall();
                } else {
                    node = ParsePropAccess();
                }
                break;

            case Lexer::HTokenType::NUM:
            case Lexer::HTokenType::STRING:
            case Lexer::HTokenType::TRUE:
            case Lexer::HTokenType::FALSE:
                case Lexer::HTokenType::NULL_LITERAL:
                // Handle literals
                node = ParseLiteral();
                break;

            case Lexer::HTokenType::LBRACKET:
                // Handle parenthesized expressions
                node = ParseExpression();
                Consume(Lexer::HTokenType::RBRACKET, "Expected closing bracket");
                break;

                // Add cases for other atomic expression types as needed

            case Lexer::HTokenType::PLUS:
            case Lexer::HTokenType::MINUS:
            case Lexer::HTokenType::NOT:
                case Lexer::HTokenType::BIT_INVERSE:
                    // Handle linebreaks
                    node = ParseUnaryExpression();
                    break;

            default:
                // Handle unexpected token type
                throw HParserError("Unexpected token in expression");
        }

        return node;
    }

    std::shared_ptr<HAstExpressionNode> HParser::ParseUnaryExpression() {
        auto exp = std::make_shared<HAstUnaryExpressionNode>();

        auto token = Consume(Lexer::HTokenFamily::OPERATOR, "Expected operator in unary expression");

        switch (token.Type) {
            case Lexer::HTokenType::PLUS:
                exp->Operator = HAstUnaryOperator(HAstOperatorType::ADD);
                break;
            case Lexer::HTokenType::MINUS:
                exp->Operator = HAstUnaryOperator(HAstOperatorType::SUBTRACT);
                break;
            case Lexer::HTokenType::NOT:
                exp->Operator = HAstUnaryOperator(HAstOperatorType::NOT);
                break;
            case Lexer::HTokenType::BIT_INVERSE:
                exp->Operator = HAstUnaryOperator(HAstOperatorType::BITWISE_NOT);
                break;
            default:
                throw HParserError("Unexpected operator in unary expression");
        }

        exp->Operand = ParseExpression();

        return exp;
    }

    std::shared_ptr<HAstStatementNode> HParser::ParseStatement(Core::HAccessLevel accessLevel) {
        auto ast = std::make_shared<HAstStatementNode>();

        auto token = Consume();

        switch (token.Type) {
            case Lexer::HTokenType::RETURN: {
                ast->Children.push_back(ParseReturnStatement());
                break;
            }
            case Lexer::HTokenType::VAR:
                ast->Children.push_back(ParseVarDecl(accessLevel, true));
                break;
            case Lexer::HTokenType::LET: {
                ast->Children.push_back(ParseVarDecl(accessLevel, false));
                break;
            }
            default:
                throw HParserError("Unexpected keyword");

        }
    }

    Lexer::HToken HParser::ParseNextNonLN() {
        auto token = Peek();
        while(token.Type == Lexer::HTokenType::LINEBREAK) {
            Consume();
            token = Peek();
        }

        return Peek();
    }

    std::int8_t HParser::GetOperatorPrecedence(HAstOperatorType type) {
        switch (type) {
            case HAstOperatorType::MULTIPLY:
            case HAstOperatorType::DIVIDE:
            case HAstOperatorType::MODULO:  // Modulo operator
                return 14;

            case HAstOperatorType::ADD:
            case HAstOperatorType::SUBTRACT:
                return 12;

            case HAstOperatorType::BITWISE_LEFT_SHIFT:
            case HAstOperatorType::BITWISE_RIGHT_SHIFT:
                return 10;  // Bit shift operators

            case HAstOperatorType::LESS_THAN:
            case HAstOperatorType::GREATER_THAN:
            case HAstOperatorType::LESS_THAN_OR_EQUAL:
            case HAstOperatorType::GREATER_THAN_OR_EQUAL:
                return 8;

            case HAstOperatorType::EQUAL:
            case HAstOperatorType::NOT_EQUAL:
                return 6;

            case HAstOperatorType::BITWISE_AND:
                return 4;

            case HAstOperatorType::BITWISE_XOR:
                return 3;

            case HAstOperatorType::BITWISE_OR:
                return 2;

            case HAstOperatorType::BITWISE_NOT:
                return 1;   // Bitwise inversion operator

            default:
                return 0;   // Non-operator tokens have the lowest precedence
        }
    }

    bool HParser::IsStatementOperator(HAstOperatorType type) {
        switch(type) {
            case HAstOperatorType::ASSIGN:
            case HAstOperatorType::ADD_ASSIGN:
            case HAstOperatorType::SUBTRACT_ASSIGN:
            case HAstOperatorType::MULTIPLY_ASSIGN:
            case HAstOperatorType::DIVIDE_ASSIGN:
                return true;
            default:
                return false;
        }
    }

    bool HParser::IsUnaryOperator(HAstOperatorType type) {
        switch (type) {
            case HAstOperatorType::ADD:
            case HAstOperatorType::SUBTRACT:
            case HAstOperatorType::BITWISE_NOT:
                return true;
            default:
                return false;
        }
    }

    std::shared_ptr<HAstNode> HParser::ParseStructDecl(Core::HAccessLevel accessLevel) {
        auto node = std::make_shared<HAstStructNode>();

        auto token = Consume(Lexer::HTokenType::STRUCT, "Expected struct keyword to start struct declaration");
            
        token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after struct declaration");
        node->Name = token.Value;

        if(Peek().Type == Lexer::HTokenType::COLON) {
            node->Inheritance = ParseInheritanceList();
        }

        token = Consume(Lexer::HTokenType::LCBRACKET, "Expected left curly bracket after class declaration");

        auto body = std::make_shared<HAstStructBodyNode>();
        node->Children.push_back(body);

        token = ParseNextNonLN();
        token = ParseNextNonLN();

        Core::HAccessLevel currentAccessLevel = Core::HAccessLevel::Internal;

        while(token.Type != Lexer::HTokenType::RCBRACKET) {
            if (token.Type == Lexer::HTokenType::PUBLIC) {
                currentAccessLevel = Core::HAccessLevel::Public;
                token = Consume();
            }
            else if (token.Type == Lexer::HTokenType::PRIVATE) {
                currentAccessLevel = Core::HAccessLevel::Private;
                token = Consume();
            }
            else if (token.Type == Lexer::HTokenType::INTERNAL) {
                currentAccessLevel = Core::HAccessLevel::Internal;
                token = Consume();
            } else if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in struct body");
            } else if(token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                body->Children.push_back(ParseVarDecl(currentAccessLevel, token.Type == Lexer::HTokenType::VAR));
            } else if(token.Type == Lexer::HTokenType::FUNC) {
                body->Children.push_back(ParseFuncDecl(currentAccessLevel));
            } else if(token.Type == Lexer::HTokenType::INIT) {
                body->Children.push_back(ParseInitDecl());
            } else {
                throw HParserError("Unexpected token in struct body");
            }

            token = ParseNextNonLN();
        }

        token = Consume(Lexer::HTokenType::RCBRACKET, "Expected right curly bracket after struct body");

        return node;
    }

    std::shared_ptr<HAstNode> HParser::ParseProtocolDecl(Core::HAccessLevel accessLevel) {
        auto node = std::make_shared<HAstProtocolNode>();

        auto token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after protocol declaration");
        node->Name = token.Value;

        if(Peek().Type == Lexer::HTokenType::COLON) {
            node->Inheritance = ParseInheritanceList();
        }

        token = Consume(Lexer::HTokenType::LCBRACKET, "Expected left curly bracket after protocol declaration");

        auto body = std::make_shared<HAstProtocolBodyNode>();

        node->Children.push_back(body);

        token = ParseNextNonLN();
        token = Consume();

        while(token.Type != Lexer::HTokenType::RCBRACKET) {
            if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in protocol body");
            } else if(token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                throw HParserError("Unexpected variable declaration in protocol body");
            } else if(token.Type == Lexer::HTokenType::FUNC) {
                body->Children.push_back(ParseFuncDecl(accessLevel));
            } else {
                throw HParserError("Unexpected token in protocol body");
            }

            token = ParseNextNonLN();
        }

        token = Consume(Lexer::HTokenType::RCBRACKET, "Expected right curly bracket after protocol body");

        return node;
    }

    std::shared_ptr<HAstNode> HParser::ParsePrototypeDecl(Core::HAccessLevel accessLevel) {
        auto node = std::make_shared<HAstPrototypeNode>();

        auto token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after prototype declaration");
        node->Name = token.Value;

        if(Peek().Type == Lexer::HTokenType::COLON) {
            node->Inheritance = ParseInheritanceList();
        }

        token = Consume(Lexer::HTokenType::LCBRACKET, "Expected left curly bracket after prototype declaration");

        auto body = std::make_shared<HAstPrototypeBodyNode>();

        Core::HAccessLevel currentAccessLevel = Core::HAccessLevel::Internal;

        while(token.Type != Lexer::HTokenType::RCBRACKET) {
            if (token.Type == Lexer::HTokenType::PUBLIC) {
                currentAccessLevel = Core::HAccessLevel::Public;
                token = Consume();
            } else if (token.Type == Lexer::HTokenType::PRIVATE) {
                currentAccessLevel = Core::HAccessLevel::Private;
                token = Consume();
            } else if (token.Type == Lexer::HTokenType::INTERNAL) {
                currentAccessLevel = Core::HAccessLevel::Internal;
                token = Consume();
            } else if(token.Type == Lexer::HTokenType::END_OF_FILE) {
                throw HParserError("Unexpected end of file in prototype body");
            } else if(token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                body->Children.push_back(ParseVarDecl(currentAccessLevel, token.Type == Lexer::HTokenType::VAR));
            } else if(token.Type == Lexer::HTokenType::FUNC) {
                body->Children.push_back(ParseFuncDecl(currentAccessLevel));
            } else {
                throw HParserError("Unexpected token in prototype body");
            }

            token = Peek();
        }

        return node;
    }

    std::shared_ptr<HAstLiteralNode> HParser::ParseString(std::string_view literal) {
        auto ast = std::make_shared<HAstLiteralNode>();
        ast->Type = "String";
        ast->Value = literal;

        return ast;
    }

    HAstOperatorType HParser::ParseOperator() {
        // Find the operator type
        auto type = HAstOperatorType::ADD;
        auto token = Peek();

        switch(token.Type) {
            // Binary operators
            case Lexer::HTokenType::PLUS:
                type = HAstOperatorType::ADD;
                break;
            case Lexer::HTokenType::MINUS:
                type = HAstOperatorType::SUBTRACT;
                break;
            case Lexer::HTokenType::MULTIPLY:
                type = HAstOperatorType::MULTIPLY;
                break;
            case Lexer::HTokenType::DIVIDE:
                type = HAstOperatorType::DIVIDE;
                break;
            case Lexer::HTokenType::MODULO:
                type = HAstOperatorType::MODULO;
                break;
            case Lexer::HTokenType::ASSIGNMENT:
				type = HAstOperatorType::ASSIGN;
				break;

            // Logical operators
            case Lexer::HTokenType::AND:
                type = HAstOperatorType::AND;
                break;
            case Lexer::HTokenType::OR:
                type = HAstOperatorType::OR;
                break;
            case Lexer::HTokenType::XOR:
                type = HAstOperatorType::XOR;
                break;
            case Lexer::HTokenType::NOT:
                type = HAstOperatorType::NOT;
                break;

            // Comparison operators
            case Lexer::HTokenType::EQUAL:
                type = HAstOperatorType::EQUAL;
                break;
            case Lexer::HTokenType::NOT_EQUAl:
                type = HAstOperatorType::NOT_EQUAL;
                break;

            default:
                throw HParserError("Unexpected operator");
        }

        return type;
    }

    std::shared_ptr<HAstMemberAccessNode> HParser::ParseMemberAccess() {
        // Member access can either access objects or self
        auto token = Consume();

        auto memberAccess = std::make_shared<HAstMemberAccessNode>();
        memberAccess->Target = token.Value;

        // Ensure we have a dot
        token = Consume(Lexer::HTokenType::DOT, "Expected dot after identifier in member access");

        // Get the member access target
        // We can either call another init, or we access a property or a function
        if(Peek(2)[1].Type == Lexer::HTokenType::LBRACKET) {
            auto funcCall = ParseFuncCall();
            memberAccess->Call = funcCall;
        } else {
            // We have a property access
            memberAccess->Call = ParsePropAccess();
        }

        return memberAccess;
    }

    [[nodiscard]] std::shared_ptr<HAstModuleDeclNode> HParser::ParseModuleDecl() {
        auto node = std::make_shared<HAstModuleDeclNode>();

		auto token = Consume(Lexer::HTokenType::MODULE, "Expected module keyword to start module declaration");

		token = Consume(Lexer::HTokenType::IDENTIFIER, "Expected identifier after module declaration");
		node->Name = token.Value;

        token = ParseNextNonLN();
        token = Peek();

        _contextStack.push(HParserContext::Module);

        Core::HAccessLevel currentAccessLevel = Core::HAccessLevel::Internal;

        while (token.Type != Lexer::HTokenType::END_OF_FILE) {
            if (token.Type == Lexer::HTokenType::PUBLIC) {
                currentAccessLevel = Core::HAccessLevel::Public;
                token = Consume();
            }
            else if (token.Type == Lexer::HTokenType::PRIVATE) {
                currentAccessLevel = Core::HAccessLevel::Private;
                token = Consume();
            }
            else if (token.Type == Lexer::HTokenType::INTERNAL) {
                currentAccessLevel = Core::HAccessLevel::Internal;
                token = Consume();
            } else if (token.Type == Lexer::HTokenType::CLASS) {
                node->Children.push_back(ParseClassDecl(currentAccessLevel));
            } 
            else if(token.Type == Lexer::HTokenType::STRUCT) {
                node->Children.push_back(ParseStructDecl(currentAccessLevel));
            } else if (token.Type == Lexer::HTokenType::VAR || token.Type == Lexer::HTokenType::LET) {
                node->Children.push_back(ParseVarDecl(currentAccessLevel, token.Type == Lexer::HTokenType::VAR));
            }
            else if (token.Type == Lexer::HTokenType::FUNC) {
                node->Children.push_back(ParseFuncDecl(currentAccessLevel));
            }
            else {
                throw HParserError("Unexpected token in module");
            }

            token = ParseNextNonLN();
            token = Peek();
        }

        _contextStack.pop();

		return node;
    }

    std::shared_ptr<HAstExpressionNode> HParser::ParseLiteral() {
        auto token = Consume();
        auto lit = std::make_shared<HAstLiteralNode>();
        // Set the type
        switch (token.Type) {
            case Lexer::HTokenType::NUM:
                lit->Type = "Number";
                break;
            case Lexer::HTokenType::STRING:
                lit->Type = "String";
                break;
            case Lexer::HTokenType::TRUE:
            case Lexer::HTokenType::FALSE:
                lit->Type = "Boolean";
                break;
            case Lexer::HTokenType::NULL_LITERAL:
                lit->Type = "Null";
                break;
            default:
                throw HParserError("Unexpected token in expression");

        }
        lit->Value = token.Value;

        return lit;
    }

    Lexer::HToken HParser::Peek() {
        return _tokens[_tokenIndex];
    }

    std::vector<Lexer::HToken> HParser::Peek(uint8_t offset) {
        return { _tokens[_tokenIndex], _tokens[_tokenIndex + 1] };
    }

    Lexer::HToken& HParser::Consume(Lexer::HTokenType expected, std::string_view error) {
        if(_tokens[_tokenIndex].Type == expected) {
            return _tokens[_tokenIndex++];
        }

        std::stringstream ss;
        ss << "Expected " << (int)expected << " but got " << (int)_tokens[_tokenIndex].Type;

        throw HParserError(ss.str());
    }

    Lexer::HToken& HParser::Consume(Lexer::HTokenFamily expected, std::string_view error) {
        if(_tokens[_tokenIndex].Family == expected) {
            return _tokens[_tokenIndex++];
        }

        throw HParserError(std::string(error));
    }

    Lexer::HToken& HParser::Consume() {
        return _tokens[_tokenIndex++];
    }
}
