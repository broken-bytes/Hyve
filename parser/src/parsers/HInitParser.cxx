#include "parser/parsers/HInitParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HInitParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}