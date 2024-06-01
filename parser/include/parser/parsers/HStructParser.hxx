#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>
#include <memory>

namespace Hyve::Parser {
	class HStructParser : public IHParser {
	public:
		explicit HStructParser(std::shared_ptr<Core::HErrorHandler> errorHandler);
		~HStructParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}