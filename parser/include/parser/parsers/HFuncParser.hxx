#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"

namespace Hyve::Parser {
	class HFuncParser : public IHParser {
	public:
		HFuncParser() = default;
		~HFuncParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;
	};
}