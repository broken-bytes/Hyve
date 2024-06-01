#include "parser/parsers/HPrototypeParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HPrototypeParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}