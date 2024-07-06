#pragma once

#include <optional>
#include <string>
#include <vector>

namespace Hyve::Lexer {
	// Token Helper constexprs
	constexpr HToken MAKE_TOKEN(
		HTokenType type, 
		HTokenFamily family,  
		std::string value, 
		size_t start, 
		size_t length
	) {
		return HToken{
			.Family = family,
			.Type = type,
			.Value = value,
			.ColumnStart = start,
			.ColumnEnd = start + length
		};
	}

	constexpr HToken UPDATE_TOKEN(
		HToken token, 
		HTokenType type, 
		HTokenFamily family, 
		std::string value, 
		size_t line,
		size_t start, 
		size_t length
	) {
		token.Family = family;
		token.Type = type;
		token.Value = value;
		token.Line = line;
		token.ColumnStart = start;
		token.ColumnEnd = start + length;

		return token;
	}


	struct HToken;
	class HProcessor {
	public:
		HProcessor() = default;
		virtual ~HProcessor() = 0;

		virtual std::optional<HToken> Process(std::string_view source) = 0;

	protected:
		const std::vector<char> operators = { '+', '-', '*', '/', '%', '^', '=', '?', '!', ':', '.' };
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
			auto oper = std::ranges::find_if(operators, [c](char op) { return op == c; });

			return oper != operators.end();
		}
	};
}