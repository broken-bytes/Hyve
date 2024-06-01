#pragma once

#include "parser/IHParser.hxx"

namespace Hyve::Parser {
	class HExpressionParser : public IHParser {
	public:
		HExpressionParser() = default;
		~HExpressionParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
	};
}