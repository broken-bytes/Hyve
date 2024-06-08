#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HExpressionParser.hxx"
#include "parser/nodes/HAstAssignmentNode.hxx"
#include <core/HErrorHandler.hxx>
#include <memory>

namespace Hyve::Parser {
	class HStatementParser : public IHParser {
	public:
		HStatementParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler,
			std::shared_ptr<HExpressionParser> exprParser
		);
		~HStatementParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HExpressionParser> _exprParser;

		std::shared_ptr<HAstAssignmentNode> ParseAssignment(Lexer::HTokenStream& stream);
	};
}