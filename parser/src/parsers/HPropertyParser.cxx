#include "parser/parsers/HPropertyParser.hxx"
#include "parser/nodes/HAstPropertyDeclNode.hxx"

namespace Hyve::Parser {
	HPropertyParser::HPropertyParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler,
		std::shared_ptr<HExpressionParser> exprParser
	) : _errorHandler(errorHandler), _exprParser(exprParser) { }

	std::shared_ptr<HAstNode> HPropertyParser::Parse(Lexer::HTokenStream& stream) {
		using enum Core::HAccessLevel;
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		auto accessLevel = ParseAccessLevel(stream);

		auto token = stream.PeekUntilNonLineBreak();

		// Ensure the next token is either var or let
		if (token.Type != VAR && token.Type != LET) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}

		auto propNode = std::make_shared<HAstPropertyDeclNode>();
		propNode->AccessLevel = accessLevel;
		propNode->IsMutable = token.Type == VAR;

		token = stream.Consume();
		token = stream.PeekUntilNonLineBreak();

		// Ensure the next token is an identifier
		if (token.Type != IDENTIFIER) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}
		token = stream.Consume();

		propNode->Name = token.Value;

		// If the next token is a colon, then we have a type annotation
		token = stream.PeekUntilNonLineBreak();
		if (token.Type == COLON) {
			stream.Consume();
			token = stream.PeekUntilNonLineBreak();

			if (token.Type != IDENTIFIER) {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}

			propNode->TypeNode = std::make_shared<HAstTypeNode>();
			propNode->TypeNode->Name = token.Value;
			stream.Consume();
		}

		// If the next token is an equal sign, then we have an initializer
		token = stream.PeekUntilNonLineBreak();
		if (token.Type == EQUAL) {
			stream.Consume();
			
			if (IsExpression(stream)) {
				auto assignNode = _exprParser->Parse(stream);
				propNode->Initializer = std::dynamic_pointer_cast<HAstExpressionNode>(assignNode);
			} else {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}
		}

		return propNode;
	}
}