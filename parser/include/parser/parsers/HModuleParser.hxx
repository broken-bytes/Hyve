#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HClassParser.hxx"
#include "parser/parsers/HVariableParser.hxx"

namespace Hyve::Parser {
	class HModuleParser : public IHParser {
	public:
		HModuleParser() = default;
		~HModuleParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(
			std::string_view fileName,
			std::vector<Lexer::HToken>& tokens
		) override;

	private:
		// Different parsers per context
		std::shared_ptr<HClassParser> _classParser;
		std::shared_ptr<HVariableParser> _varParser;
	};
}