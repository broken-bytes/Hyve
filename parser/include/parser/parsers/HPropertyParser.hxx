#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HExpressionParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HPropertyParser : public IHParser {
	public:
		explicit HPropertyParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler,
			std::shared_ptr<HExpressionParser> exprParser
		);
		~HPropertyParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HExpressionParser> _exprParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}