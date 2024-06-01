#include "parser/parsers/HFuncParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HFuncParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}