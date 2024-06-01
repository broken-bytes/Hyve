#include "parser/parsers/HTypeParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HTypeParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}