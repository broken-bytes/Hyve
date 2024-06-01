#include "parser/parsers/HVariableParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HVariableParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}