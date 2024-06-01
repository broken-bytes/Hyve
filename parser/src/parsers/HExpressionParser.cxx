#include "parser/parsers/HExpressionParser.hxx"

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HExpressionParser::Parse(
		std::string_view,
		std::vector<Lexer::HToken>& tokens
	) {
		return nullptr;
	}
}