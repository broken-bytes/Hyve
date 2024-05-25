#pragma once

#include "parser/HAst.hxx"
#include "parser/HAstNode.hxx"
#include "parser/HParserContex.hxx"
#include "parser/HAstOperatorType.hxx"
#include "parser/nodes/HAstFuncDeclNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/nodes/HAstFuncCallNode.hxx"
#include "parser/nodes/HAstFuncBodyNode.hxx"
#include "parser/nodes/HAstMemberAccessNode.hxx"
#include "parser/nodes/HAstPropAccessNode.hxx"
#include "parser/nodes/HAstVarDeclNode.hxx"
#include "parser/nodes/HAstBinaryExpressionNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include "parser/nodes/HAstReturnNode.hxx"
#include "parser/nodes/HAstLiteralNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"

#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>

#include <queue>
#include <string>
#include <vector>

namespace Hyve::Parser {
    class HParser {
        public:
        HParser();

        [[nodiscard]] std::shared_ptr<HAstNode> Parse(std::vector<Lexer::HToken>& tokens);

    private:
        std::vector<Lexer::HToken> _tokens;
        uint64_t _tokenIndex;
        std::queue<HParserContext> _contextStack;

        // Condition Checks
        bool CanStartStatement();
        bool CanStartExpression();

        [[nodiscard]] std::shared_ptr<HAstVarDeclNode> ParseVarDecl(bool isMutable);
        [[nodiscard]] std::shared_ptr<HAstReturnNode> ParseReturnStatement();
        [[nodiscard]] std::shared_ptr<HAstNode> ParseFuncDecl();
        [[nodiscard]] std::shared_ptr<HAstNode> ParseInitDecl();
        [[nodiscard]] std::shared_ptr<HAstPropAccessNode> ParsePropAccess();
        [[nodiscard]] std::shared_ptr<HAstFuncBodyNode> ParseFuncBody();
        [[nodiscard]] std::shared_ptr<HAstFuncCallNode> ParseFuncCall();
        [[nodiscard]] std::vector<HAstParamater> ParseParameters();
        [[nodiscard]] std::shared_ptr<HAstTypeNode> ParseType(std::shared_ptr<HAstTypeNode> parent = nullptr);
        [[nodiscard]] std::shared_ptr<HAstNode> ParseClassDecl();
        [[nodiscard]] std::shared_ptr<HAstInheritanceNode> ParseInheritanceList();
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseExpression();
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseExpressionWithPrecedence(int precedence);
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseAtomicExpression();
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseUnaryExpression();
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseBinaryExpression();
        [[nodiscard]] std::shared_ptr<HAstStatementNode> ParseStatement();
        [[nodiscard]] Lexer::HToken ParseNextNonLN();
        [[nodiscard]] std::int8_t GetOperatorPrecedence(HAstOperatorType type);
        /**
         * Check if the operator is a statement operator.
         * @param type The operator type.
         * @return True if the operator is a statement operator. All compound operators are statement operators, as well as the assignment operator.
         */
        [[nodiscard]] bool IsStatementOperator(HAstOperatorType type);
        [[nodiscard]] bool IsUnaryOperator(HAstOperatorType type);
        [[nodiscard]] std::shared_ptr<HAstNode> ParseEnumDecl();
        [[nodiscard]] std::shared_ptr<HAstNode> ParseStructDecl();
        [[nodiscard]] std::shared_ptr<HAstNode> ParseProtocolDecl();
        [[nodiscard]] std::shared_ptr<HAstNode> ParsePrototypeDecl();
        [[nodiscard]] std::shared_ptr<HAstLiteralNode> ParseString(std::string_view literal);
        [[nodiscard]] HAstOperatorType ParseOperator();
        [[nodiscard]] std::shared_ptr<HAstMemberAccessNode> ParseMemberAccess();
        [[nodiscard]] std::shared_ptr<HAstExpressionNode> ParseLiteral();
        [[nodiscard]] Lexer::HToken Peek();
        [[nodiscard]] std::vector<Lexer::HToken> Peek(uint8_t offset);
        /*
         * Consume a token of a specific type, or throw an error if the type mismatched.
         */
        [[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenType expected, std::string_view error);
        /*
         * Consume a token of a specific family, or throw an error if the type mismatched.
         */
        [[nodiscard]] Lexer::HToken& Consume(Lexer::HTokenFamily expected, std::string_view error);
        /*
         * Consome a token without checking the type.
         */
        [[maybe_unused]] Lexer::HToken& Consume();
    };
}
