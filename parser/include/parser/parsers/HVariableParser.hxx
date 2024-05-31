#pragma once

#include "parser/IHParser.hxx"

namespace Hyve::Parser {
	class HVariableParser : public IHParser {
	public:
		HVariableParser() = default;
		~HVariableParser() final = default;

		virtual std::shared_ptr<HAstNode> Parse(
			std::string_view fileName,
			std::vector<Lexer::HToken>& tokens
		) override;

	private:
		// Different parsers per context
	};
}