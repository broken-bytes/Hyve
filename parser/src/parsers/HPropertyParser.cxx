#include "parser/parsers/HPropertyParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HPropertyParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}