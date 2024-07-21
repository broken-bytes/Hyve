#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"

namespace Hyve::Parser {
	class HEnumParser final : public IHParser {
	public:
		HEnumParser() = default;
		~HEnumParser() final = default;

		virtual std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HPropertyParser> _propParser;
	};
}