#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HTypeParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::AST {
	struct HAstNode;
}

namespace Hyve::Parser {
	class HInheritanceParser final : public IHParser {
	public:
		explicit HInheritanceParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler
		);
		~HInheritanceParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
	};
}