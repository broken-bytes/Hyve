#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"

namespace Hyve::Parser {
	class HExpressionParser : public IHParser {
	public:
		HExpressionParser() = default;
		~HExpressionParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HPropertyParser> _propParser;
	};
}