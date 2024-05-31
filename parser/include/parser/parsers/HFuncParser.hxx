#pragma once

#include "parser/IHParser.hxx"

namespace Hyve::Parser {
	class HFuncParser : public IHParser {
	public:
		HFuncParser() = default;
		~HFuncParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(
			std::string_view fileName,
			std::vector<Lexer::HToken>& tokens
		) override;

	private:
		// Different parsers per context
		std::shared_ptr<HVariableParser> _varParser;
	};
}