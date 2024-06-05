#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include "parser/HAstParameter.hxx"
#include <core/HErrorHandler.hxx>
#include <vector>

namespace Hyve::Parser {
	class HFuncParser : public IHParser {
	public:
		explicit HFuncParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HFuncParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;

		std::vector<HAstParamater> ParseParameters(Lexer::HTokenStream& stream);
		std::shared_ptr<HAstTypeNode> ParseReturnType(Lexer::HTokenStream& stream);
		std::shared_ptr<HAstNode> ParseBody(Lexer::HTokenStream& stream);
	};
}