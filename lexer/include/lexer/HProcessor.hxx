#pragma once

#include "lexer/HToken.hxx"
#include "lexer/HTokenOperators.hxx"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace Hyve::Lexer {
	// Token Helper constexprs
	constexpr HToken MAKE_TOKEN(
		HTokenType type, 
		const std::string& value
	) {
		return HToken {
			.Family = GetFamily(type),
			.Type = type,
			.Value = value,
			.ColumnStart = 0,
			.ColumnEnd = value.size()
		};
	}

	constexpr HToken UPDATE_TOKEN(
		HToken token, 
		size_t line,
		size_t start
	) {
		token.Line = line;
		token.ColumnStart = start;
		token.ColumnEnd = start + token.ColumnEnd;

		return token;
	}

	struct HToken;
	class HProcessor {
	public:
		HProcessor() = default;
		virtual ~HProcessor() = 0;

		virtual std::optional<HToken> Process(std::string_view source) = 0;

	protected:
		const std::vector<std::string> operators = { 
			Operators::OPERATOR_ADD,
			Operators::OPERATOR_SUB,
			Operators::OPERATOR_MUL,
			Operators::OPERATOR_DIV,
			Operators::OPERATOR_MOD,
			Operators::OPERATOR_POW,
			Operators::OPERATOR_INC,
			Operators::OPERATOR_DEC,
			Operators::OPERATOR_ASSIGN,
			Operators::OPERATOR_ADD_ASSIGN,
			Operators::OPERATOR_SUB_ASSIGN,
			Operators::OPERATOR_MUL_ASSIGN,
			Operators::OPERATOR_DIV_ASSIGN,
			Operators::OPERATOR_MOD_ASSIGN,
			Operators::OPERATOR_POW_ASSIGN,
			Operators::OPERATOR_AND,
			Operators::OPERATOR_OR,
			Operators::OPERATOR_XOR,
			Operators::OPERATOR_NOT,
			Operators::OPERATOR_AND_ASSIGN,
			Operators::OPERATOR_OR_ASSIGN,
			Operators::OPERATOR_XOR_ASSIGN,
			Operators::OPERATOR_NOT_ASSIGN,
			Operators::OPERATOR_AND_AND,
			Operators::OPERATOR_OR_OR,
			Operators::OPERATOR_EQUAL,
			Operators::OPERATOR_NOT_EQUAL,
			Operators::OPERATOR_LESS,
			Operators::OPERATOR_GREATER,
			Operators::OPERATOR_LESS_EQUAL,
			Operators::OPERATOR_GREATER_EQUAL,
			Operators::OPERATOR_SHIFT_LEFT,
			Operators::OPERATOR_SHIFT_RIGHT,
			Operators::OPERATOR_SHIFT_LEFT_ASSIGN,
			Operators::OPERATOR_SHIFT_RIGHT_ASSIGN,
			Operators::OPERATOR_TERNARY,
			Operators::OPERATOR_ARROW,
			Operators::OPERATOR_DOT
		};
		/**
		* @brief Drops characters until a non-whitespace character is found. EOF is considered a whitespace character.
		* @param token The token to process.
		* @return The index of the first non-whitespace character.
		*/
		size_t DropWhitespace(std::string_view source) const {
			// Drop whitespaces until a non-whitespace character is found.
			size_t index = 0;
			while (index < source.size() && std::isspace(source[index])) {
				++index;
			}

			// Return the index of the first non-whitespace character 
			// so we know what column the next token starts at.
			return index;
		}

		/**
		* @brief Check if the character is an operator.
		* @param c The character to check.
		* @return True if the character is an operator, false otherwise.
		*/
		bool IsOperator(char c) const {
			auto oper = std::ranges::find_if(operators, [c](std::string_view op) { return op.contains(c); });

			return oper != operators.end();
		}

		/**
		* @brief Checks if source is a valid sequence defined by target.
		* @param source The source string to check.
		* @param target The target string to check against.
		* @return True if source is a valid sequence defined by target, false otherwise.
		* @note The sequence must either only contain the target string or an operator must follow the target string.
		*/
		bool CheckMatchingSequence(std::string_view source, std::string_view target) const {
			if (
				source.starts_with(target) &&
				source.size() > target.size() &&
				IsOperator(source.substr(target.size()).front())
			) {
				return true;
			}

			return false;
		}

		HToken HandleError(std::string_view source, std::string_view message) const {
			auto token = MAKE_TOKEN(HTokenType::ERROR, std::string(source));
			token.Error = message;

			return token;
		}
	};
}