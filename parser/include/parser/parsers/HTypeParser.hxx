#pragma once

#include "parser/IHParser.hxx"
#include <memory>

namespace Hyve::Parser {
	class HTypeParser : public IHParser {
	public:
		HTypeParser() = default;
		~HTypeParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
	};
}