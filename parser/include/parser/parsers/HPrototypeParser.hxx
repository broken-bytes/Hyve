#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <memory>

namespace Hyve::Parser {
	class HPrototypeParser final : public IHParser {
	public:
		HPrototypeParser() = default;
		~HPrototypeParser() final = default;

		virtual std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}