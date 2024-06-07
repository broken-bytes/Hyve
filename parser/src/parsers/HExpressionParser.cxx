#include "parser/parsers/HExpressionParser.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"

namespace Hyve::Parser {
	HExpressionParser::HExpressionParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler
	) : _errorHandler(errorHandler) { }

	std::shared_ptr<HAstNode> HExpressionParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		std::shared_ptr<HAstExpressionNode> exprNode = nullptr;

		auto token = stream.Peek();

		// As long as the token is a valid expression token, keep parsing
		while (CanBeInExpression(stream)) {

		}

		return nullptr;
	}

	std::shared_ptr<HAstFuncCallNode> HExpressionParser::ParseFuncCall(Lexer::HTokenStream& stream) {
		return nullptr;
	}

	std::shared_ptr<HAstUnaryExpressionNode> HExpressionParser::ParseUnaryExpression(Lexer::HTokenStream& stream) {

		return nullptr;
	}

	std::shared_ptr<HAstBinaryExpressionNode> HExpressionParser::ParseBinaryExpression(Lexer::HTokenStream& stream) {
		return nullptr;
	}
}