#include "parser/parsers/HProtocolParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HProtocolParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}