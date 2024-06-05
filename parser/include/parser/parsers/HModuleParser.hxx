#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HClassParser.hxx"
#include "parser/parsers/HEnumParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"
#include "parser/parsers/HProtocolParser.hxx"
#include "parser/parsers/HPrototypeParser.hxx"
#include "parser/parsers/HStructParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	class HModuleParser : public IHParser {
	public:
		HModuleParser(
			const std::shared_ptr<Core::HErrorHandler>& errorHandler,
			const std::shared_ptr<HClassParser>& _classParser,
			const std::shared_ptr<HEnumParser>& _enumParser,
			const std::shared_ptr<HFuncParser>& _funcParser,
			const std::shared_ptr<HPropertyParser>& _propParser,
			const std::shared_ptr<HProtocolParser>& _protocolParser,
			const std::shared_ptr<HPrototypeParser>& _prototypeParser,
			const std::shared_ptr<HStructParser>& _structParser,
			const std::shared_ptr<HVariableParser>& _varParser
		);
		~HModuleParser() final = default;

		std::shared_ptr<HAstNode> Parse(Lexer::HTokenStream& stream) override;

	private:
		std::shared_ptr<Core::HErrorHandler> _errorHandler;
		// Different parsers per context
		std::shared_ptr<HClassParser> _classParser;
		std::shared_ptr<HEnumParser> _enumParser;
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HPropertyParser> _propParser;
		std::shared_ptr<HProtocolParser> _protocolParser;
		std::shared_ptr<HPrototypeParser> _prototypeParser;
		std::shared_ptr<HStructParser> _structParser;
		std::shared_ptr<HVariableParser> _varParser;

		void HandleErrorCase(Lexer::HTokenStream& stream);
	};
}