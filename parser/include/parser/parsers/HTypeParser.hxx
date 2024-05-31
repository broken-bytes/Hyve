#pragma once

#include "parser/IHParser.hxx"

namespace Hyve::Parser {
	class HTypeParser : public IHParser {
	public:
		HTypeParser() = default;
		~HTypeParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(
			std::string_view fileName,
			std::vector<Lexer::HToken>& tokens
		) override;

	private:
		// Different parsers per context
		std::shared_ptr<HFuncParser> _funcParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}