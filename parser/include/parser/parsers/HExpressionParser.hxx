#pragma once

#include "parser/IHParser.hxx"
#include "parser/nodes/HAstBinaryExpressionNode.hxx"
#include "parser/nodes/HAstFuncCallNode.hxx"
#include "parser/nodes/HAstUnaryExpressionNode.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HExpressionParser : public IHParser {
	public:
		explicit HExpressionParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HExpressionParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;

		// Func call parser
		std::shared_ptr<HAstFuncCallNode> ParseFuncCall(Lexer::HTokenStream& stream);
		// Unary expression parser
		std::shared_ptr<HAstUnaryExpressionNode> ParseUnaryExpression(Lexer::HTokenStream& stream);
		// Binary expression parser
		std::shared_ptr<HAstBinaryExpressionNode> ParseBinaryExpression(Lexer::HTokenStream& stream);
	};
}