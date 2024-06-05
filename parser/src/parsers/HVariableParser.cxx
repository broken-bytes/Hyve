#include "parser/parsers/HVariableParser.hxx"
#include "parser/nodes/HAstVarDeclNode.hxx"
#include <lexer/HTokenType.hxx>

namespace Hyve::Parser {
	HVariableParser::HVariableParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler,
		std::shared_ptr<HExpressionParser> expressionParser
	) : _errorHandler(errorHandler), 
		_expressionParser(expressionParser) {}

	std::shared_ptr<HAstNode> HVariableParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		using enum HAstNodeType;
		using enum Core::HCompilerError::ErrorCode;
		
		auto token = stream.Peek();

		// Check if the next token is a variable(var or let)
		if (token.Type != VAR && token.Type != LET) {
			// Panic until keyword is found
			Panic(stream, KEYWORD);
			return nullptr;
		}

		// Consume the variable keyword
		token = stream.Consume();

		// Create a new variable node
		auto variable = std::make_shared<HAstVarDeclNode>();

		// Set the variable type
		variable->IsMutable = token.Type == VAR;

		// Ensure the next token is an identifier
		token = stream.Peek();

		if (token.Type != IDENTIFIER) {
			_errorHandler->AddError(MISSING_VARIABLE_NAME, token.FileName, token.Line);
			// Panic until identifier is found
			Panic(stream, KEYWORD);
			return nullptr;
		}

		// Consume the identifier
		token = stream.Consume();

		// Set the variable name
		variable->Name = token.Value;

		// Check if we have a type annotation
		token = stream.Peek();

		if (token.Type == COLON) {
			// Consume the colon
			stream.Consume();

			// Parse the type
			variable->TypeNode = ParseType(stream);
		}

		// Check if we have an assignment
		token = stream.Peek();

		if (token.Type == EQUAL) {
			// Consume the equal sign
			stream.Consume();

			// Parse the expression
			variable->Initializer = std::dynamic_pointer_cast<HAstExpressionNode>(_expressionParser->Parse(stream));
		}

		return variable;
	}
}