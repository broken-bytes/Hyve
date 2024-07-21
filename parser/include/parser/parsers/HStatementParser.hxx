#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HExpressionParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>
#include <memory>

namespace Hyve::AST {
	struct HAstAssignmentNode;
	struct HAstNode;
}

namespace Hyve::Parser {
	class HStatementParser final : public IHParser {
	public:
		HStatementParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler,
			std::shared_ptr<HExpressionParser> exprParser,
			std::shared_ptr<HVariableParser> varParser
		);
		~HStatementParser() final = default;

		virtual std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HExpressionParser> _exprParser;
		std::shared_ptr<HVariableParser> _varParser;

		std::shared_ptr<AST::HAstAssignmentNode> ParseAssignment(Lexer::HTokenStream& stream);
	};
}