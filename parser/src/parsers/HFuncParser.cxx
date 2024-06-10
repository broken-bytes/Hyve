#include "parser/parsers/HFuncParser.hxx"
#include "parser/nodes/HAstFuncDeclNode.hxx"
#include "parser/nodes/HAstBlockNode.hxx"
#include <core/HCompilerError.hxx>

namespace Hyve::Parser {
	HFuncParser::HFuncParser(std::shared_ptr<Core::HErrorHandler> errorHandler) : _errorHandler(errorHandler) { }

	std::shared_ptr<HAstNode> HFuncParser::Parse(Lexer::HTokenStream& stream) {
		using enum Core::HAccessLevel;
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		auto accessLevel = ParseAccessLevel(stream);

		auto token = stream.PeekUntilNonLineBreak();

		// Ensure the next token is either var or let
		if (token.Type != FUNC) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			Panic(stream, KEYWORD);
		}

		stream.Consume();

		// Create a new function node
		auto funcNode = std::make_shared<HAstFuncDeclNode>();
		funcNode->AccessLevel = accessLevel;

		// Parse the function name
		if (token = stream.PeekUntilNonLineBreak(); token.Type != IDENTIFIER) {
			_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
			// Check if the next token is an opening parenthesis, if so, we can assume the function name is missing.
			// In this case we provide an error message DONT panic but generate a node with a missing name
			if(token.Type == LBRACKET) {
				_errorHandler->AddError(MISSING_FUNCTION_NAME, token.FileName, token.Line);
				funcNode->Name = "";
			} else {
				// Unrecoverable function, we panic until the next keyword
				_errorHandler->AddError(INVALID_FUNCTION_DECLARATION, token.FileName, token.Line);
				Panic(stream, KEYWORD);
			}
		}

		token = stream.Consume();

		// Set the function name
		funcNode->Name = token.Value;

		// Parse the function parameters
		funcNode->Parameters = ParseParameters(stream);

		// Parse the return type
		funcNode->ReturnType = ParseReturnType(stream);

		// Parse the function body
		if(auto body = ParseBody(stream); body != nullptr) {
			funcNode->Children.push_back(body);
			body->Parent = funcNode;
		}

		return funcNode;
	}

	std::vector<HAstParamater> HFuncParser::ParseParameters(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		std::vector<HAstParamater> parameters;

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

	std::shared_ptr<HAstTypeNode> HFuncParser::ParseReturnType(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum Core::HCompilerError::ErrorCode;

		// Parse the function return type
		auto token = stream.PeekUntilNonLineBreak();

		if (token.Type != ARROW) {
			// If the return type is missing, we provide an error message and generate a node with a missing return type
			if (token.Type == LCBRACKET) {
				_errorHandler->AddError(MISSING_FUNCTION_RETURN_TYPE, token.FileName, token.Line);
				
				return nullptr;
			}
			else {
				_errorHandler->AddError(UnexpectedToken, token.FileName, token.Line);
				Panic(stream, KEYWORD);
				
				return nullptr;
			}
		}
		
		// We have a return type, consume the arrow token
		stream.Consume();

		auto returnType = std::make_shared<HAstTypeNode>();

		if (token = stream.PeekUntilNonLineBreak(); token.Type != IDENTIFIER) {
			_errorHandler->AddError(MISSING_FUNCTION_RETURN_TYPE, token.FileName, token.Line);
			// Check if the next token is an opening curly brace, if so, we can assume the return type is missing.
			// In this case we provide an error message DONT panic but generate a node with a missing name
			if (token.Type == LCBRACKET) {
				_errorHandler->AddError(MISSING_FUNCTION_RETURN_TYPE, token.FileName, token.Line);
				return nullptr;
			} else {
				// Unrecoverable function, we panic until the next keyword
				_errorHandler->AddError(INVALID_FUNCTION_DECLARATION, token.FileName, token.Line);
				Panic(stream, KEYWORD);
				return nullptr;
			}
		}

		token = stream.Consume();
		returnType->Name = token.Value;

		return returnType;
	}

	std::shared_ptr<HAstNode> HFuncParser::ParseBody(Lexer::HTokenStream& stream) {
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