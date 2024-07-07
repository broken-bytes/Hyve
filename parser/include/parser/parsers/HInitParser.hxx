#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::AST {
	struct HAstNode;
	struct HAstParamater;
}

namespace Hyve::Parser {
	class HInitParser : public IHParser {
	public:
		explicit HInitParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HInitParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;

		std::vector<AST::HAstParamater> ParseParameters(Lexer::HTokenStream& stream);
		std::shared_ptr<AST::HAstNode> ParseBody(Lexer::HTokenStream& stream);
	};
}