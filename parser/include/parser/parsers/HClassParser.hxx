#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"
#include <lexer/HTokenStream.hxx>

namespace Hyve::Parser {
	class HClassParser : public IHParser {
	public:
		HClassParser() = default;
		~HClassParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

		private:
			// Different parsers per context
			std::shared_ptr<HFuncParser> _funcParser;
			std::shared_ptr<HPropertyParser> _propParser;
	};
}