#include "parser/parsers/HStatementParser.hxx"
#include <ast/nodes/HAstAssignmentNode.hxx>
#include <ast/nodes/HAstIdentifierNode.hxx>
#include <ast/nodes/HAstReturnNode.hxx>
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <lexer/HTokenStream.hxx>

namespace Hyve::Parser {
	using namespace AST;

	HStatementParser::HStatementParser(
		std::shared_ptr<Core::HErrorHandler> errorHandler,
		std::shared_ptr<HExpressionParser> exprParser,
		std::shared_ptr<HVariableParser> varParser
	) : _errorHandler(errorHandler), _exprParser(exprParser), _varParser(varParser) {}

	std::shared_ptr<HAstNode> HStatementParser::Parse(Lexer::HTokenStream& stream) {
		using enum Lexer::HTokenType;
		using enum Lexer::HTokenFamily;
		// Parse the first token
		auto token = stream.Peek();

		if (token.Type == IDENTIFIER) {
			// Check if the next token is an assignment operator
			auto nextToken = stream.Peek(2)[1];

			if (nextToken.Type == ASSIGNMENT) {
				// Parse an assignment
				return ParseAssignment(stream);
			}
		} else if (token.Type == VAR || token.Type == LET) {
			// Parse a variable declaration
			return _varParser->Parse(stream);
		}
		else if (token.Type == RETURN) {
			auto returnNode = std::make_shared<HAstReturnNode>();
			
			// Consumes the return keyword
			stream.Consume();

			// Parse the return value(if any)
			// First, peek the next token and check if it is a keyword or a brace. If so, return an empty return statement
			token = stream.PeekUntilNonLineBreak();

			if (token.Family == KEYWORD || token.Family == GROUPING) {
				return returnNode;
			}

			returnNode->Value = std::dynamic_pointer_cast<HAstExpressionNode>(_exprParser->Parse(stream));

			return returnNode;
		}

		return nullptr;
	}

	std::shared_ptr<HAstAssignmentNode> HStatementParser::ParseAssignment(Lexer::HTokenStream& stream) {
		auto token = stream.Consume();

		auto identifier = std::make_shared<HAstIdentifierNode>();
		identifier->Name = token.Value;

		// Consumes the assignment operator
		token = stream.Consume();
		
		auto assignment = std::make_shared<HAstAssignmentNode>();
		// TODO: Check the actual type of assignment operator
		assignment->Operator = HAstOperatorType::ASSIGN;
		assignment->Target = identifier;
		assignment->Value = std::dynamic_pointer_cast<HAstExpressionNode>(_exprParser->Parse(stream));

		return assignment;
	}
}