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

		// The next token should be an opening brace
		stream.Consume(LCBRACKET);

		// Parse the body of the struct
		auto bodyNode = std::make_shared<HAstStructBodyNode>();
		structNode->Children.push_back(bodyNode);

		while (stream.Peek().Type != RCBRACKET) {
			if (IsProperty(stream)) {
				bodyNode->Children.push_back(_propParser->Parse(stream));
			} else if (IsFunc(stream)) {
				bodyNode->Children.push_back(_funcParser->Parse(stream));
			} else {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}
		}

		if (stream.Peek().Type == RCBRACKET) {
			stream.Consume(RCBRACKET);
		}
		else {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}

		return structNode;
	}
}