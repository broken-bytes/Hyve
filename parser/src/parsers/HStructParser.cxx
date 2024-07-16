#include "parser/parsers/HStructParser.hxx"
#include <ast/HAstNode.hxx>
#include <ast/nodes/HAstStructBodyNode.hxx>
#include <ast/nodes/HAstStructNode.hxx>
#include <ast/nodes/HAstTypeNode.hxx>
#include <ast/nodes/HAstInheritanceNode.hxx>
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <lexer/HTokenStream.hxx>
#include <core/HCompilerError.hxx>
#include <core/HErrorHandler.hxx>

namespace Hyve::Parser {
	using namespace AST;

	HStructParser::HStructParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler,
		std::shared_ptr<HFuncParser> funcParser,
		std::shared_ptr<HInheritanceParser> inheritanceParser,
		std::shared_ptr<HInitParser> initParser,
		std::shared_ptr<HPropertyParser> propParser
	) : _errorHandler(errorHandler), 
		_funcParser(funcParser), 
		_inheritanceParser(inheritanceParser),
		_initParser(initParser),
		_propParser(propParser) { }

	std::shared_ptr<HAstNode> HStructParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;
		using enum HParserContext;

		auto structNode = std::make_shared<HAstStructNode>();

		// A struct may have an access modifier
		auto accessLevel = ParseAccessLevel(stream);

		// A Struct always starts with the struct keyword
		auto token = stream.Consume(STRUCT);

		// The next token should be the name of the struct
		auto name = stream.Consume(IDENTIFIER);

		SetContext(Struct);

		structNode->Inheritance = std::dynamic_pointer_cast<HAstInheritanceNode>(_inheritanceParser->Parse(stream));
		structNode->Name = name.Value;

		if(auto body = ParseStructBody(stream); body != nullptr) {
			body->Parent = structNode;
			structNode->Children.push_back(body);
		}

		// Ensure we have a closing brace
		token = stream.Consume();

		// If we don't have a closing brace, emit an error but continue
		if (token.Type != CURLY_RIGHT) {
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

		if (token.Type != CURLY_LEFT) {
			stream.Consume();

			// We have something in front of the opening brace, ignore it and continue
			if (stream.Peek().Type == CURLY_LEFT) {
				stream.Consume();
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			} else {
				// We have an unrecoverable error, panic
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, CURLY_LEFT);
				
				return nullptr;
			}

			return nullptr;
		}

		token = stream.Consume();

		// Create the body of the struct
		// Parse the body of the struct
		auto bodyNode = std::make_shared<HAstStructBodyNode>();

		// Ensure we have an opening brace
		token = stream.PeekUntilNonLineBreak();

		while (token.Type != CURLY_RIGHT) {
			if (IsProperty(stream)) {
				if (auto prop = _propParser->Parse(stream); prop != nullptr) {
					prop->Parent = bodyNode;
					bodyNode->Children.push_back(prop);
				}
			} else if (IsFunc(stream)) {
				if(auto func = _funcParser->Parse(stream); func != nullptr) {
					func->Parent = bodyNode;
					bodyNode->Children.push_back(func);
				}
			} else if (IsInit(stream)) {
				if (auto init = _initParser->Parse(stream); init != nullptr) {
					init->Parent = bodyNode;
					bodyNode->Children.push_back(init);
				}
			} else {
				// We have an unrecoverable error, panic
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, CURLY_RIGHT);

				return bodyNode;				
			}

			token = stream.PeekUntilNonLineBreak();
		}

		// Consume the closing brace
		token = stream.Consume();

		return bodyNode;
	}
}