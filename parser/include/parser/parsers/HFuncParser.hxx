#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>
#include <vector>

namespace Hyve::AST {
	struct HAstParamater;
	struct HAstTypeNode;
	struct HAstNode;
}

namespace Hyve::Parser {
	class HFuncParser : public IHParser {
	public:
		explicit HFuncParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HFuncParser() final = default;

		std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;

		std::vector<AST::HAstParamater> ParseParameters(Lexer::HTokenStream& stream);
		std::shared_ptr<AST::HAstTypeNode> ParseReturnType(Lexer::HTokenStream& stream);
		std::shared_ptr<AST::HAstNode> ParseBody(Lexer::HTokenStream& stream);
	};
}