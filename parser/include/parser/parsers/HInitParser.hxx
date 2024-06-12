#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include "parser/HAstParameter.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HInitParser : public IHParser {
	public:
		explicit HInitParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HInitParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;

		std::vector<HAstParamater> ParseParameters(Lexer::HTokenStream& stream);
		std::shared_ptr<HAstNode> ParseBody(Lexer::HTokenStream& stream);
	};
}