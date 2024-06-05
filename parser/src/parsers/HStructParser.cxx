#include "parser/parsers/HStructParser.hxx"
#include "parser/nodes/HAstStructBodyNode.hxx"
#include "parser/nodes/HAstStructNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"
#include <lexer/HTokenType.hxx>
#include <core/HCompilerError.hxx>
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	HStructParser::HStructParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler,
		std::shared_ptr<HFuncParser> funcParser,
		std::shared_ptr<HInheritanceParser> inheritanceParser,
		std::shared_ptr<HPropertyParser> propParser
	) : _errorHandler(errorHandler), 
		_funcParser(funcParser), 
		_inheritanceParser(inheritanceParser),
		_propParser(propParser) { }

	std::shared_ptr<HAstNode> HStructParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;
		using enum HParserContext;

		auto structNode = std::make_shared<HAstStructNode>();

		// A Struct always starts with the struct keyword
		auto token = stream.Consume(STRUCT);

		// The next token should be the name of the struct
		auto name = stream.Consume(IDENTIFIER);

		SetContext(Struct);

		structNode->Inheritance = std::dynamic_pointer_cast<HAstInheritanceNode>(_inheritanceParser->Parse(stream));
		structNode->Name = name.Value;

		structNode->Children.push_back(ParseStructBody(stream));

		// Ensure we have a closing brace
		token = stream.Consume();

		// If we don't have a closing brace, emit an error but continue
		if (token.Type != RCBRACKET) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
		}

		return structNode;
	}

	std::shared_ptr<HAstStructBodyNode> HStructParser::ParseStructBody(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;
		using enum HParserContext;

		// The next token should be an opening brace
		auto token = stream.PeekUntilNonLineBreak();

		if (token.Type != LCBRACKET) {
			stream.Consume();

			// We have something in fron of the opening brace, ignore it and continue
			if (stream.Peek().Type == LCBRACKET) {
				stream.Consume();
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			} else {
				// We have an unrevoered error, panic
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, LCBRACKET);
				
				return nullptr;
			}

			return nullptr;
		}

		stream.Consume();

		// Create the body of the struct
		// Parse the body of the struct
		auto bodyNode = std::make_shared<HAstStructBodyNode>();

		// Ensure we have an opening brace
		token = stream.PeekUntilNonLineBreak();

		while (token.Type != RCBRACKET) {
			if (IsProperty(stream)) {
				bodyNode->Children.push_back(_propParser->Parse(stream));
			} else if (IsFunc(stream)) {
				bodyNode->Children.push_back(_funcParser->Parse(stream));
			} else {
				// We have an unrevoered error, panic
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, RCBRACKET);
				
				return nullptr;
			}

			token = stream.PeekUntilNonLineBreak();
		}

		return bodyNode;
	}
}