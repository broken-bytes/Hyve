#include "parser/parsers/HEnumParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HEnumParser::Parse(
		std::string_view, 
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}