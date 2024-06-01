#pragma once

#include "parser/parsers/HClassParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HClassParser::Parse(
		std::string_view, 
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}