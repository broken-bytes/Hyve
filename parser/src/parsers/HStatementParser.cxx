#include "parser/parsers/HStatementParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HStatementParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}