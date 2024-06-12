#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HInheritanceParser.hxx"
#include "parser/parsers/HInitParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"
#include "parser/nodes/HAstStructBodyNode.hxx"
#include <core/HErrorHandler.hxx>
#include <memory>

namespace Hyve::Parser {
	class HStructParser : public IHParser {
	public:
		explicit HStructParser(
			std::shared_ptr<Core::HErrorHandler> errorHandler,
			std::shared_ptr<HFuncParser> funcParser,
			std::shared_ptr<HInheritanceParser> inheritanceParser,
			std::shared_ptr<HInitParser> initParser,
			std::shared_ptr<HPropertyParser> propParser
		);
		~HStructParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HInheritanceParser> _inheritanceParser;
		std::shared_ptr<HInitParser> _initParser;
		std::shared_ptr<HPropertyParser> _propParser;

		std::shared_ptr<HAstStructBodyNode> ParseStructBody(Lexer::HTokenStream& stream);
	};
}