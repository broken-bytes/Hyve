#include "parser/parsers/HInitParser.hxx"
#include "parser/nodes/HAstBlockNode.hxx"
#include "parser/nodes/HAstInitDeclNode.hxx"
#include <core/HAccessLevel.hxx>

namespace Hyve::Parser {
	HInitParser::HInitParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler
	) : _errorHandler(errorHandler) {}

	std::shared_ptr<HAstNode> HInitParser::Parse(Lexer::HTokenStream& stream) {
		using enum Core::HAccessLevel;
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		auto accessLevel = ParseAccessLevel(stream);

		auto token = stream.PeekUntilNonLineBreak();

		// Ensure the next token is INIT
		if (token.Type != INIT) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}

		stream.Consume();

		// Create a new function node
		auto initNode = std::make_shared<HAstInitDeclNode>();
		initNode->AccessLevel = accessLevel;

		token = stream.PeekUntilNonLineBreak();

		// Parse the function parameters
		initNode->Parameters = ParseParameters(stream);

		// Parse the init body
		if (auto body = ParseBody(stream); body != nullptr) {
			initNode->Children.push_back(body);
			body->Parent = initNode;
		}

		return initNode;
	}

	std::vector<HAstParamater> HInitParser::ParseParameters(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		std::vector<HAstParamater> parameters = {};

		auto token = stream.PeekUntilNonLineBreak();

		// Ensure the next token is an opening parenthesis
		if (token.Type != LBRACKET) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}

		stream.Consume();

		token = stream.PeekUntilNonLineBreak();

		// Parse the parameters
		while (token.Type != RBRACKET) {
			// Parse the parameter name
			if (token.Type != IDENTIFIER) {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}

			stream.Consume();

			auto parameter = HAstParamater();
			parameter.Name = token.Value;

			// Parse the parameter type
			if (token = stream.PeekUntilNonLineBreak(); token.Type != COLON) {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}

			stream.Consume();

			if (token = stream.PeekUntilNonLineBreak(); token.Type != IDENTIFIER) {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}

			stream.Consume();

			parameter.Type = std::make_shared<HAstTypeNode>();
			parameter.Type->Name = token.Value;

			parameters.push_back(parameter);

			// Check if there are more parameters
			if (token = stream.PeekUntilNonLineBreak(); token.Type == COMMA) {
				stream.Consume();
			}

			token = stream.PeekUntilNonLineBreak();
		}

		stream.Consume();

		return parameters;
	}

	std::shared_ptr<HAstNode> HInitParser::ParseBody(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		// Check if the next token is an opening curly brace
		auto token = stream.PeekUntilNonLineBreak();

		// We return gracefully if the body is missing because some types allow functions without bodies(like interfaces)
		if (token.Type != LCBRACKET) {
			return nullptr;
		}

		stream.Consume();

		// Parse the body
		auto body = std::make_shared<HAstBlockNode>();

		token = stream.PeekUntilNonLineBreak();

		// Parse statements and expressions one by one
		while (token.Type != RCBRACKET) {
			// TODO: Implement statement and expression parsing
			token = stream.Consume();
		}

		token = stream.Consume();

		return body;
	}
}