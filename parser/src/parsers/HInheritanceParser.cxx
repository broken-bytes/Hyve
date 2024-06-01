#include "parser/parsers/HInheritanceParser.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	HInheritanceParser::HInheritanceParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler
	) : _errorHandler(errorHandler) {}

	std::shared_ptr<HAstNode> HInheritanceParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		if (stream.Peek().Type == COLON) {
			auto inheritanceNode = std::make_shared<HAstInheritanceNode>();

			// Consume the colon
			auto token = stream.Consume(COLON);

			// While the next token is not a left curly brace we keep parsing the inheritance
			while (stream.Peek().Type != LCBRACKET) {
				auto inheritance = stream.Consume(IDENTIFIER);
				auto typeNode = std::make_shared<HAstTypeNode>();
				typeNode->Name = inheritance.Value;

				inheritanceNode->Children.push_back(typeNode);

				token = stream.Peek();

				// If the next token is a comma, consume it
				if (token.Type == COMMA) {
					token = stream.Consume(COMMA);
				}
				else if (token.Type == IDENTIFIER) {
					// If the next token is an identifier, we have a syntax error
					// We should have a comma
					// Report the error and skip the token
					_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
					// Panic: Skip Until the curly brace
					Panic(stream, LCBRACKET);
				}
			}

			return inheritanceNode;
		}

		return nullptr;
	}
}