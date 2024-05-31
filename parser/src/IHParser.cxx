#include "parser/IHParser.hxx"
#include "parser/nodes/HAstArrayNode.hxx"
#include <core/HCompilerError.hxx>
#include <sstream>

namespace Hyve::Parser {
	void IHParser::SetTokens(const std::vector<Lexer::HToken>& tokens) {
		_tokens = tokens;
		_tokenIndex = 0;
	}

	bool IHParser::CanStartStatement() {
		auto token = Peek();

		switch (token.Type) {
		case Lexer::HTokenType::RETURN:
		case Lexer::HTokenType::VAR:
		case Lexer::HTokenType::LET:
		case Lexer::HTokenType::IDENTIFIER:
		case Lexer::HTokenType::SELF:
			return true;
		default:
			return false;
		}
	}

	[[nodiscard]] bool IHParser::CanStartExpression() {
		auto token = Peek();

		switch (token.Type) {
		case Lexer::HTokenType::IDENTIFIER:
		case Lexer::HTokenType::STRING:
		case Lexer::HTokenType::TRUE:
		case Lexer::HTokenType::FALSE:
		case Lexer::HTokenType::NULL_LITERAL:
		case Lexer::HTokenType::NUM:
			return true;
		default:
			return false;
		}
	}

	[[nodiscard]] bool IHParser::IsExpression() {
		if (!CanStartExpression()) {
			return false;
		}

		auto token = IHParser::ParseNextNonLN();
		token = Peek();

		for (uint64_t x = _tokenIndex; x < _tokens.size(); x++) {
			if (token.Type == Lexer::HTokenType::DOT || token.Type == Lexer::HTokenType::IDENTIFIER) {
				// We have an identifier or member access, thus we need to proceed
				continue;
			}
			else if (
				token.Type == Lexer::HTokenType::PLUS ||
				token.Type == Lexer::HTokenType::MINUS ||
				token.Type == Lexer::HTokenType::MULTIPLY ||
				token.Type == Lexer::HTokenType::DIVIDE
				) {
				// Binary expression, so this is an expression
				return true;
			}

			token = ParseNextNonLN();
			token = Peek();
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsStatement() {
		if (!CanStartStatement()) {
			return false;
		}

		auto token = ParseNextNonLN();
		token = Peek();

		for (uint64_t x = _tokenIndex; x < _tokens.size(); x++) {
			if (token.Type == Lexer::HTokenType::DOT || token.Type == Lexer::HTokenType::IDENTIFIER) {
				// We have an identifier or member access, thus we need to proceed
				continue;
			}
			else if (
				token.Type == Lexer::HTokenType::ASSIGNMENT ||
				token.Type == Lexer::HTokenType::PLUS_ASSIGN ||
				token.Type == Lexer::HTokenType::MINUS_ASSIGN ||
				token.Type == Lexer::HTokenType::MULTIPLY_ASSIGN ||
				token.Type == Lexer::HTokenType::DIVIDE_ASSIGN
				) {
				// Assignment, so this is a statement
				return true;
			}

			token = ParseNextNonLN();
			token = Peek();
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsClass() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if(token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == CLASS) {
				return true;
			}
		}

		if (token.Type == Lexer::HTokenType::CLASS) {
			return true;
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsEnum() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == ENUM) {
				return true;
			}
		}

		if (token.Type == Lexer::HTokenType::ENUM) {
			return true;
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsFunc() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == FUNC) {
				return true;
			}
		}

		if (token.Type == Lexer::HTokenType::FUNC) {
			return true;
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsProtocol() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == PROTOCOL) {
				return true;
			}
		}

		if (token.Type == Lexer::HTokenType::PROTOCOL) {
			return true;
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsPrototype() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == PROTOTYPE) {
				return true;
			}
		}

		if (token.Type == Lexer::HTokenType::PROTOTYPE) {
			return true;
		}

		return false;
	}

	[[nodiscard]] bool IHParser::IsStruct() {
		using enum Lexer::HTokenType;
		auto token = ParseNextNonLN();
		token = Peek();

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == STRUCT) {
				return true;
			}
		}
		if (token.Type == Lexer::HTokenType::STRUCT) {
			return true;
		}

		return false;
	}

	[[nodiscard]] std::int8_t IHParser::GetOperatorPrecedence(HAstOperatorType type) {
		switch (type) {
		case HAstOperatorType::MULTIPLY:
		case HAstOperatorType::DIVIDE:
		case HAstOperatorType::MODULO:  // Modulo operator
			return 14;

		case HAstOperatorType::ADD:
		case HAstOperatorType::SUBTRACT:
			return 12;

		case HAstOperatorType::BITWISE_LEFT_SHIFT:
		case HAstOperatorType::BITWISE_RIGHT_SHIFT:
			return 10;  // Bit shift operators

		case HAstOperatorType::LESS_THAN:
		case HAstOperatorType::GREATER_THAN:
		case HAstOperatorType::LESS_THAN_OR_EQUAL:
		case HAstOperatorType::GREATER_THAN_OR_EQUAL:
			return 8;

		case HAstOperatorType::EQUAL:
		case HAstOperatorType::NOT_EQUAL:
			return 6;

		case HAstOperatorType::BITWISE_AND:
			return 4;

		case HAstOperatorType::BITWISE_XOR:
			return 3;

		case HAstOperatorType::BITWISE_OR:
			return 2;

		case HAstOperatorType::BITWISE_NOT:
			return 1;   // Bitwise inversion operator

		default:
			return 0;   // Non-operator tokens have the lowest precedence
		}
	}

	[[nodiscard]] bool IHParser::IsStatementOperator(HAstOperatorType type) {
		switch (type) {
		case HAstOperatorType::ASSIGN:
		case HAstOperatorType::ADD_ASSIGN:
		case HAstOperatorType::SUBTRACT_ASSIGN:
		case HAstOperatorType::MULTIPLY_ASSIGN:
		case HAstOperatorType::DIVIDE_ASSIGN:
			return true;
		default:
			return false;
		}
	}

	[[nodiscard]] bool IHParser::IsUnaryOperator(HAstOperatorType type) {
		switch (type) {
		case HAstOperatorType::ADD:
		case HAstOperatorType::SUBTRACT:
		case HAstOperatorType::BITWISE_NOT:
			return true;
		default:
			return false;
		}
	}

	[[nodiscard]] Lexer::HToken& IHParser::Consume(Lexer::HTokenFamily expected, std::string_view error) {
		if (_tokens[_tokenIndex].Family == expected) {
			_tokenIndex++;

			return _tokens[_tokenIndex];
		}

		throw Core::HCompilerError(
			Core::HCompilerError::ErrorCode::UnexpectedToken, 
			_tokens[_tokenIndex].FileName,
			_tokens[_tokenIndex].Line
		);
	}

	[[nodiscard]] Lexer::HToken& IHParser::Consume(Lexer::HTokenType expected, std::string_view error) {
		if (_tokens[_tokenIndex].Type == expected) {
			_tokenIndex++;
			
			return _tokens[_tokenIndex];
		}

		throw Core::HCompilerError(
			Core::HCompilerError::ErrorCode::UnexpectedToken,
			_tokens[_tokenIndex].FileName,
			_tokens[_tokenIndex].Line
		);
	}

	[[maybe_unused]] Lexer::HToken& IHParser::Consume() {
		_tokenIndex++;

		return _tokens[_tokenIndex];
	}

	[[nodiscard]] Lexer::HToken IHParser::ParseNextNonLN() {
		auto token = Peek();
		while (token.Type == Lexer::HTokenType::LINEBREAK) {
			Consume();
			token = Peek();
		}

		return Peek();
	}

	[[nodiscard]] std::shared_ptr<HAstExpressionNode> IHParser::ParseLiteral() {
		auto token = Consume();
		auto lit = std::make_shared<HAstLiteralNode>();
		// Set the type
		switch (token.Type) {
		case Lexer::HTokenType::NUM:
			lit->Type = "Number";
			break;
		case Lexer::HTokenType::STRING:
			lit->Type = "String";
			break;
		case Lexer::HTokenType::TRUE:
		case Lexer::HTokenType::FALSE:
			lit->Type = "Boolean";
			break;
		case Lexer::HTokenType::NULL_LITERAL:
			lit->Type = "Null";
			break;
		default:
			throw Core::HCompilerError(
				Core::HCompilerError::ErrorCode::UnexpectedToken,
				token.FileName,
				token.Line
			);

		}
		lit->Value = token.Value;

		return lit;
	}

	[[nodiscard]] std::shared_ptr<HAstLiteralNode> IHParser::ParseString(std::string_view literal) {
		auto ast = std::make_shared<HAstLiteralNode>();
		ast->Type = "String";
		ast->Value = literal;

		return ast;
	}

	[[nodiscard]] std::shared_ptr<HAstTypeNode> IHParser::ParseType(std::shared_ptr<HAstTypeNode> parent = nullptr) {
		auto token = Consume();

		// We expect an identifier -> Regular type
		if (token.Type == Lexer::HTokenType::IDENTIFIER) {
			auto type = std::make_shared<HAstTypeNode>();
			type->Name = token.Value;

			if (parent != nullptr) {
				if (Peek().Type == Lexer::HTokenType::RSBRACKET && parent->Name == "Array") {
					Consume();
					std::shared_ptr<HAstArrayNode> array = dynamic_pointer_cast<HAstArrayNode>(parent);
					array->Type = type;
					type = array;
				}
				else {
					throw Core::HCompilerError(
						Core::HCompilerError::ErrorCode::TypeMismatch,
						token.FileName,
						token.Line
					);
				}
			}

			return type;
		}
		// We expect an open bracket -> Array type
		else if (token.Type == Lexer::HTokenType::LSBRACKET) {
			auto array = std::make_shared<HAstArrayNode>();
			array->Name = "Array";
			array->Type = ParseType(array);
			return array;
		}
		else {
			throw Core::HCompilerError(
				Core::HCompilerError::ErrorCode::TypeMismatch,
				token.FileName,
				token.Line
			);
		}
	}

	[[nodiscard]] Lexer::HToken IHParser::Peek() {
		return _tokens[_tokenIndex];
	}

	[[nodiscard]] std::vector<Lexer::HToken> IHParser::Peek(uint8_t offset) {
		return { _tokens[_tokenIndex], _tokens[_tokenIndex + 1] };
	}
}