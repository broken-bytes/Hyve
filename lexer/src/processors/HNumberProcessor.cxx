#include "lexer/processors/HNumberProcessor.hxx"
#include "lexer/HToken.hxx"
#include <iostream>

namespace Hyve::Lexer {
	std::optional<HToken> HNumberProcessor::Process(std::string_view source) {
		if (source.empty()) {
			return std::nullopt;
		}

		// Check if the first character is a digit.
		// If it is not, we can return early.
		if (!std::isdigit(source.front())) {
			return std::nullopt;
		}

		// Validation criteria for numbers:
		// - Check if no invalid characters are present.(e.g. letters, except for 0x 0b)
		// - Check if the number is a float(has a dot somewhere).
		// - Check if the number is a hex.(starts with 0x)
		// - Check if the number is a binary.(starts with 0b)
		// - If none of the above, it is an integer.

		if (auto integerLit = ProcessInteger(source); integerLit.has_value()) {
			return integerLit;
		}

		if(auto floatLit = ProcessFloat(source); floatLit.has_value()) {
			return floatLit;
		}

		if(auto hexLit = ProcessHex(source); hexLit.has_value()) {
			return hexLit;
		}

		if(auto binaryLit = ProcessBinary(source); binaryLit.has_value()) {
			return binaryLit;
		}

		return std::nullopt;
	}

	std::optional<HToken> HNumberProcessor::ProcessInteger(std::string_view source) const {
		using enum HTokenFamily;
		using enum HTokenType;
		// Parse numbers until the source ends or an operator is found.
		// Any other character (e.g. a letter) will emit an error.
		std::string number;
		for (auto c : source) {
			if (std::isdigit(c)) {
				number.push_back(c);
			}
			else if (isalpha(c)) {
				return HandleError(source, "Unexpected character in number literal.");
			}
			else if (c == '.') {
				// If a dot is found, the number might be a float so we return early.
				return std::nullopt;
			}
			else if(IsOperator(c)) {
				break;
			}
		}

		if (number.empty()) {
			return std::nullopt;
		}

		// Initialize the token and return it.
		// Note: The column start and end are not accurate are relative to the source.
		// This is because the source is a substring of the original source.
		// The lexer will handle this by adding the offset of the source to the column start and end.
		// Additionally, line and file information will be added by the lexer.
		return MAKE_TOKEN(INTEGER, number);
	}

	std::optional<HToken> HNumberProcessor::ProcessFloat(std::string_view source) const {
		using enum HTokenFamily;
		using enum HTokenType;

		bool hasDot = false;
		std::string number;

		for (auto c : source) {
			if (std::isdigit(c)) {
				number.push_back(c);
			}
			else if (isalpha(c)) {
				return HandleError(source, "Unexpected character in number literal.");
			}
			else if (c == '.') {
				if (hasDot) {
					return HandleError(source, "Unexpected dot in number literal.");
				}
				hasDot = true;
				number.push_back(c);
			}
			else if (IsOperator(c)) {
				break;
			}
		}

		if (number.empty()) {
			return std::nullopt;
		}

		// Same as the integer literal, some information is not accurate.
		return MAKE_TOKEN(FLOAT, number);
	}

	std::optional<HToken> HNumberProcessor::ProcessHex(std::string_view source) const {
		using enum HTokenFamily;
		using enum HTokenType;

		if (source.size() < 3) {
			return std::nullopt;
		}

		if (source[0] != '0' || source[1] != 'x') {
			return std::nullopt;
		}

		std::string number;
		for (size_t i = 2; i < source.size(); i++) {
			if (std::isxdigit(source[i])) {
				number.push_back(source[i]);
			}
			else if (isalpha(source[i])) {
				return HandleError(source, "Unexpected character in hex literal.");
			}
			else if (IsOperator(source[i])) {
				break;
			}
		}

		if (number.empty()) {
			return std::nullopt;
		}

		return MAKE_TOKEN(INTEGER, number);
	}

	std::optional<HToken> HNumberProcessor::ProcessBinary(std::string_view source) const {
		using enum HTokenFamily;
		using enum HTokenType;

		if (source.size() < 3) {
			return std::nullopt;
		}

		if (source[0] != '0' || source[1] != 'b') {
			return std::nullopt;
		}

		std::string number;
		for (size_t i = 2; i < source.size(); i++) {
			if (source[i] == '0' || source[i] == '1') {
				number.push_back(source[i]);
			}
			else if (isalpha(source[i])) {
				return HandleError(source, "Unexpected character in binary literal.");
			}
			else if (IsOperator(source[i])) {
				break;
			}
		}

		if (number.empty()) {
			return std::nullopt;
		}

		return MAKE_TOKEN(INTEGER, number);
	}
}