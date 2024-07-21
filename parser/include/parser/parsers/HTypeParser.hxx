#pragma once

#include "parser/IHParser.hxx"
#include <memory>

namespace Hyve::AST {
	struct HAstNode;
}

namespace Hyve::Parser {
	class HTypeParser final : public IHParser {
	public:
		HTypeParser() = default;
		~HTypeParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		// Different parsers per context
	};
}