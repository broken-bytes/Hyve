#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HTypeParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HInheritanceParser : public IHParser {
	public:
		HInheritanceParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler
		);
		~HInheritanceParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
	};
}