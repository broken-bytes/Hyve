#include "parser/parsers/HExpressionParser.hxx"
#include <ast/nodes/HAstBinaryExpressionNode.hxx>
#include <ast/nodes/HAstExpressionNode.hxx>
#include <ast/nodes/HAstFuncCallNode.hxx>
#include <ast/nodes/HAstPropAccessNode.hxx>
#include <ast/nodes/HAstIdentifierNode.hxx>
#include <ast/nodes/HAstMemberAccessNode.hxx>
#include <ast/nodes/HAstUnaryExpressionNode.hxx>
#include <lexer/HToken.hxx>
#include <lexer/HTokenStream.hxx>

namespace Hyve::Parser {
	using namespace AST;

	HExpressionParser::HExpressionParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler
	) : _errorHandler(errorHandler) { }

	std::shared_ptr<HAstNode> HExpressionParser::Parse(Lexer::HTokenStream& stream) {
		return ParseExpression(stream, 0);
	}

	std::shared_ptr<HAstExpressionNode> HExpressionParser::ParseExpression(
		Lexer::HTokenStream& stream, 
		uint16_t precedence
	) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;

		auto token = stream.PeekUntilNonLineBreak();
		std::shared_ptr<HAstExpressionNode> left;

		if (IsUnaryOperator(GetOperatorType(token))) {
			left = ParseUnaryExpression(stream);
		} else if (token.Type == IDENTIFIER) {
			auto nextToken = stream.Peek(2)[1];
			// We need to check if the next token is a dot operator
			if (nextToken.Type == DOT) {
				left = ParseMemberAccess(stream);
			} else if(nextToken.Type == PAREN_LEFT) {
				left = ParseFuncCall(stream);
			} else {
				// Consume the identifier
				token = stream.Consume();
				auto identifierNode = std::make_shared<HAstIdentifierNode>();
				identifierNode->Name = token.Value;

				left = identifierNode;
			}
		}

		token = stream.PeekUntilNonLineBreak();

		// If the next token is not an operator, we return the left-hand side
		if (token.Family != OPERATOR) {
			return left;
		}

		while (true) {
			token = stream.Peek();
			// Safeguard, if we have reached the end of the stream
			if (token.Type == Lexer::HTokenType::END_OF_FILE) {
				break;
			}
			auto opType = GetOperatorType(token);
			auto tokenPrecedence = GetOperatorPrecedence(opType);

			if (tokenPrecedence < precedence) {
				break;
			}

			stream.Consume(); // Consume the operator
			auto right = ParseExpression(stream, tokenPrecedence + 1); // Parse right-hand side with higher precedence
			auto binaryNode = std::make_shared<HAstBinaryExpressionNode>();
			binaryNode->Operator = opType;
			binaryNode->LHS = left;
			binaryNode->RHS = right;

			left = binaryNode;

		}

		return left;
	}

	std::shared_ptr<HAstFuncCallNode> HExpressionParser::ParseFuncCall(Lexer::HTokenStream& stream) const {
		auto funcCall = std::make_shared<HAstFuncCallNode>();

		// Consume the identifier
		auto token = stream.Consume();
		auto identifierNode = std::make_shared<HAstIdentifierNode>();
		identifierNode->Name = token.Value;
		funcCall->Target = identifierNode;

		// Consume the left bracket
		token = stream.Consume();

		// TODO: Parse the arguments
		token = stream.Consume();

		return funcCall;
	}

	std::shared_ptr<HAstUnaryExpressionNode> HExpressionParser::ParseUnaryExpression(Lexer::HTokenStream& stream) const {
		return nullptr;
	}

	std::shared_ptr<HAstBinaryExpressionNode> HExpressionParser::ParseBinaryExpression(Lexer::HTokenStream& stream) const {
		return nullptr;
	}

	std::shared_ptr<HAstPropAccessNode> HExpressionParser::ParsePropAccess(Lexer::HTokenStream& stream) const {
		auto token = stream.Consume();

		auto propAccess = std::shared_ptr<HAstPropAccessNode>();

		return propAccess;
	}

	std::shared_ptr<HAstExpressionNode> HExpressionParser::ParseMemberAccess(Lexer::HTokenStream& stream) const {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		// Consume the identifier
		auto token = stream.Consume();

		auto memberAccess = std::make_shared<HAstMemberAccessNode>();
		auto target = std::make_shared<HAstIdentifierNode>();
		target->Name = token.Value;
		memberAccess->Target = target;

		// Now parse the member -> Consume the dot operator
		token = stream.Consume();

		// Parse as long as we have a dot operator
		while(token.Type == DOT) {
			// Consume the dot operator
			token = stream.Consume();
			// We need to make sure that the next token is an identifier
			if (token.Type != IDENTIFIER) {
				_errorHandler->AddError(INVALID_EXPRESSION, token.FileName, token.Line);
				Panic(stream, KEYWORD);
				
				return memberAccess;
			}

			// We need to check if the current memberAccess has a member.
			// If it does, we need to create a new member node and set it as the member of the current memberAccess
			// If it doesn't, we need to set the current memberAccess as the member of the new member node

			if (memberAccess->Member == nullptr) {
				// Create a new member node
				auto memberNode = std::make_shared<HAstIdentifierNode>();
				memberNode->Name = token.Value;
				memberAccess->Member = memberNode;
			} else {
				// Create a new member node
				auto newMemberAccessNode = std::make_shared<HAstMemberAccessNode>();
				auto memberNode = std::make_shared<HAstIdentifierNode>();
				memberNode->Name = token.Value;
				newMemberAccessNode->Member = memberNode;
				memberAccess->Member = newMemberAccessNode;
				// Set the new node as the current memberAccess, so that we can continue to add members
				memberAccess = newMemberAccessNode;
			}

			// Peek the next token
			token = stream.Peek();
		}

		// We only need to check if the next token is a left bracket
		// If it is, we need to parse the function call
		// If it is not we return a prop access node
		if (token.Type == BRACKET_LEFT) {
			auto funcCall = ParseFuncCall(stream);
			funcCall->Target = memberAccess;

			return funcCall;
		} else {
			auto propAccess = std::make_shared<HAstPropAccessNode>();
			propAccess->Target = memberAccess;

			return propAccess;
		}
	}
}