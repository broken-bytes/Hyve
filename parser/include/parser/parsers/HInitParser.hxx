#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"

namespace Hyve::Parser {
	class HInitParser : public IHParser {
	public:
		HInitParser() = default;
		~HInitParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;
	};
}