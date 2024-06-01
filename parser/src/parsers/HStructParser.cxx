#include "parser/parsers/HStructParser.hxx"
#include "parser/nodes/HAstStructNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"
#include <lexer/HTokenType.hxx>
#include <core/HCompilerError.hxx>
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	HStructParser::HStructParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler
	) : _errorHandler(errorHandler) {

	}

	std::shared_ptr<HAstNode> HStructParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Core::HCompilerError::ErrorCode;

		auto structNode = std::make_shared<HAstStructNode>();

		// A Struct always starts with the struct keyword

		auto token = stream.Consume(STRUCT);

		// The next token should be the name of the struct
		auto name = stream.Consume(IDENTIFIER);

		structNode->Name = name.Value;

		// Structs may inherit from other prototypes/protocols
		// We can check that by checking if the next token is a colon
		if (stream.Peek().Type == COLON) {
			auto inheritanceNode = std::make_shared<HAstInheritanceNode>();

			// Consume the colon
			token = stream.Consume(COLON);

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
		}

		return structNode;
	}
}