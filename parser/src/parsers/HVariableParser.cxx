#include "parser/parsers/HVariableParser.hxx"
#include "parser/nodes/HAstVarDeclNode.hxx"
#include <lexer/HTokenType.hxx>

namespace Hyve::Parser {
	std::shared_ptr<HAstNode> HVariableParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum HAstNodeType;
		// Check if the next token is a variable(var or let)
		if (auto token = stream.Peek(); token.Type != VAR && token.Type != LET) {
			// Panic until keyword is found
			Panic(stream, KEYWORD);
		}

		// Consume the variable keyword
		stream.Consume();

		// Create a new variable node
		auto variable = std::make_shared<HAstVarDeclNode>();

		return variable;
	}
}