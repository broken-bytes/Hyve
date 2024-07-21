#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HExpressionParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HVariableParser final : public IHParser {
	public:
		HVariableParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler,
			std::shared_ptr<HExpressionParser> expressionParser
		);
		~HVariableParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HExpressionParser> _expressionParser;
	};
}