#include "parser/IHParser.hxx"
#include "parser/HParser.hxx"
#include "parser/parsers/HClassParser.hxx"
#include "parser/parsers/HEnumParser.hxx"
#include "parser/parsers/HFuncParser.hxx"
#include "parser/parsers/HModuleParser.hxx"
#include "parser/parsers/HPropertyParser.hxx"
#include "parser/parsers/HProtocolParser.hxx"
#include "parser/parsers/HPrototypeParser.hxx"
#include "parser/parsers/HStructParser.hxx"
#include "parser/parsers/HVariableParser.hxx"
#include "parser/nodes/HAstArrayNode.hxx"
#include <core/HCompilerError.hxx>
#include <core/HErrorHandler.hxx>
#include <sstream>
#include <string_view>

namespace Hyve::Parser {
	void IHParser::SetFile(std::string_view file) {
		_file = file;
	}

	void IHParser::SetTokens(const std::vector<Lexer::HToken>& tokens) {
		_tokens = tokens;
		_tokenIndex = 0;
	}

	bool IHParser::CanStartStatement() {
		using enum Lexer::HTokenType;

		auto token = IHParser::ParseNextNonLN();
		token = Peek();

		switch (token.Type) {
			case RETURN:
			case VAR:
			case LET:
			case IDENTIFIER:
			case SELF:
				return true;
			default:
				return false;
		}
	}

	bool IHParser::CanStartExpression() {
		using enum Lexer::HTokenType;

		auto token = IHParser::ParseNextNonLN();
		token = Peek();

		switch (token.Type) {
			case IDENTIFIER:
			case STRING:
			case TRUE:
			case FALSE:
			case NULL_LITERAL:
			case NUM:
				return true;
			default:
				return false;
		}
	}

	bool IHParser::IsExpression() {
		using enum Lexer::HTokenType;

		if (!CanStartExpression()) {
			return false;
		}

		auto token = IHParser::ParseNextNonLN();
		token = Peek();

		for (uint64_t x = _tokenIndex; x < _tokens.size(); x++) {
			if (token.Type == DOT || token.Type == IDENTIFIER) {
				// We have an identifier or member access, thus we need to proceed
				continue;
			}
			else if (
				token.Type == PLUS ||
				token.Type == MINUS ||
				token.Type == MULTIPLY ||
				token.Type == DIVIDE
				) {
				// Binary expression, so this is an expression
				return true;
			}

			token = ParseNextNonLN();
			token = Peek();
		}

		return false;
	}

	bool IHParser::IsStatement() {
		using enum Lexer::HTokenType;

		if (!CanStartStatement()) {
			return false;
		}

		auto token = ParseNextNonLN();
		token = Peek();

		for (uint64_t x = _tokenIndex; x < _tokens.size(); x++) {
			if (token.Type == DOT || token.Type == IDENTIFIER) {
				// We have an identifier or member access, thus we need to proceed
				continue;
			}
			else if (
				token.Type == ASSIGNMENT ||
				token.Type == PLUS_ASSIGN ||
				token.Type == MINUS_ASSIGN ||
				token.Type == MULTIPLY_ASSIGN ||
				token.Type == DIVIDE_ASSIGN
				) {
				// Assignment, so this is a statement
				return true;
			}

			token = ParseNextNonLN();
			token = Peek();
		}

		return false;
	}

	bool IHParser::IsClass() {
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

		if (token.Type == CLASS) {
			return true;
		}

		return false;
	}

	bool IHParser::IsEnum() {
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

		if (token.Type == ENUM) {
			return true;
		}

		return false;
	}

	bool IHParser::IsFunc() {
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

		if (token.Type == FUNC) {
			return true;
		}

		return false;
	}

	bool IHParser::IsProperty() {
		using enum Lexer::HTokenType;
		using enum HParserContext;
		auto token = ParseNextNonLN();
		token = Peek();

		if (GetContext() != Class) {
			return false;
		}

		if (token.Type == PUBLIC || token.Type == PRIVATE || token.Type == INTERNAL) {
			// We need to skip the access modifier, as it is optional. Peek two tokens ahead
			auto tokens = Peek(2);

			if (tokens[1].Type == VAR || tokens[1].Type == LET) {
				return true;
			}
		}

		if (token.Type == VAR || token.Type == LET) {
			return true;
		}

		return false;
	}

	bool IHParser::IsProtocol() {
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

		if (token.Type == PROTOCOL) {
			return true;
		}

		return false;
	}

	bool IHParser::IsPrototype() {
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

		if (token.Type == PROTOTYPE) {
			return true;
		}

		return false;
	}

	bool IHParser::IsStruct() {
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
		if (token.Type == STRUCT) {
			return true;
		}

		return false;
	}

	bool IHParser::IsVariable() {
		using enum Lexer::HTokenType;
		using enum HParserContext;
		auto token = ParseNextNonLN();
		token = Peek();

		if (GetContext() == Class) {
			return false;
		}

		if (token.Type == VAR || token.Type == LET) {
			return true;
		}

		return false;
	}

	std::int8_t IHParser::GetOperatorPrecedence(HAstOperatorType type) const {
		using enum HAstOperatorType;

		switch (type) {
			case MULTIPLY:
			case DIVIDE:
			case MODULO:  // Modulo operator
				return 14;

			case ADD:
			case SUBTRACT:
				return 12;

			case BITWISE_LEFT_SHIFT:
			case BITWISE_RIGHT_SHIFT:
				return 10;  // Bit shift operators

			case LESS_THAN:
			case GREATER_THAN:
			case LESS_THAN_OR_EQUAL:
			case GREATER_THAN_OR_EQUAL:
				return 8;

			case EQUAL:
			case NOT_EQUAL:
				return 6;

			case BITWISE_AND:
				return 4;

			case BITWISE_XOR:
				return 3;

			case BITWISE_OR:
				return 2;

			case BITWISE_NOT:
				return 1;   // Bitwise inversion operator

			default:
				return 0;   // Non-operator tokens have the lowest precedence
		}
	}

	bool IHParser::IsStatementOperator(HAstOperatorType type) const {
		using enum HAstOperatorType;

		switch (type) {
			case ASSIGN:
			case ADD_ASSIGN:
			case SUBTRACT_ASSIGN:
			case MULTIPLY_ASSIGN:
			case DIVIDE_ASSIGN:
				return true;
			default:
				return false;
		}
	}

	bool IHParser::IsUnaryOperator(HAstOperatorType type) const {
		using enum HAstOperatorType;

		switch (type) {
			case ADD:
			case SUBTRACT:
			case BITWISE_NOT:
				return true;
			default:
				return false;
		}
	}

	Lexer::HToken& IHParser::Consume(Lexer::HTokenFamily expected) {
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

	Lexer::HToken& IHParser::Consume(Lexer::HTokenType expected) {
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

	Lexer::HToken& IHParser::Consume() {
		_tokenIndex++;

		return _tokens[_tokenIndex];
	}

	Lexer::HToken IHParser::ParseNextNonLN() {
		auto token = Peek();
		while (token.Type == Lexer::HTokenType::LINEBREAK) {
			Consume();
			token = Peek();
		}

		return Peek();
	}

	std::shared_ptr<HAstExpressionNode> IHParser::ParseLiteral() {
		using enum Lexer::HTokenType;

		auto token = Consume();
		auto lit = std::make_shared<HAstLiteralNode>();
		// Set the type
		switch (token.Type) {
			case NUM:
				lit->Type = "Number";
				break;
			case STRING:
				lit->Type = "String";
				break;
			case TRUE:
			case FALSE:
				lit->Type = "Boolean";
				break;
			case NULL_LITERAL:
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

	std::shared_ptr<HAstLiteralNode> IHParser::ParseString(std::string_view literal) const {
		auto ast = std::make_shared<HAstLiteralNode>();
		ast->Type = "String";
		ast->Value = literal;

		return ast;
	}

	std::shared_ptr<HAstTypeNode> IHParser::ParseType(std::shared_ptr<HAstTypeNode> parent) {
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

	Lexer::HToken IHParser::Peek() const {
		return _tokens[_tokenIndex];
	}

	std::vector<Lexer::HToken> IHParser::Peek(uint8_t numTokens) const {
		std::vector<Lexer::HToken> tokens;

		for (uint8_t x = 0; x < numTokens; x++) {
			tokens.push_back(_tokens[_tokenIndex + x - 1]);
		}

		return tokens;
	}

	HParserContext IHParser::GetContext() const {
		return _context;
	}

	void IHParser::SetContext(HParserContext ctx) {
		_context = ctx;
	}

	std::unique_ptr<IHParser> Create() {
		auto errorHandler = std::make_shared<Core::HErrorHandler>();
		auto classParser = std::make_shared<HClassParser>();
		auto enumParser = std::make_shared<HEnumParser>();
		auto funcParser = std::make_shared<HFuncParser>();
		auto propParser = std::make_shared<HPropertyParser>();
		auto protocolParser = std::make_shared<HProtocolParser>();
		auto prototypeParser = std::make_shared<HPrototypeParser>();
		auto structParser = std::make_shared<HStructParser>();
		auto varParser = std::make_shared<HVariableParser>();
		auto moduleParser = std::make_shared<HModuleParser>(
			errorHandler,
			classParser,
			enumParser,
			funcParser,
			propParser,
			protocolParser,
			prototypeParser,
			structParser,
			varParser
		);

		return std::make_unique<Hyve::Parser::HParser>(errorHandler, moduleParser);
	}
}