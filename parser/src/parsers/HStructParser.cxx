#include "parser/parsers/HStructParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HStructParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}