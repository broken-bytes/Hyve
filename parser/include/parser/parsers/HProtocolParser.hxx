#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HVariableParser.hxx"

namespace Hyve::Parser {
	class HProtocolParser : public IHParser {
	public:
		HProtocolParser() = default;
		~HProtocolParser() final = default;

		virtual std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}