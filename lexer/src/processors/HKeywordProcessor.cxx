#include "lexer/processors/HKeywordProcessor.hxx"
#include "lexer/HToken.hxx"
#include <optional>

namespace Hyve::Lexer {
	std::optional<HToken> HKeywordProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;

		// No keyword is less than 2 characters
		if (source.size() < 2) {
			return std::nullopt;
		}

		// Check if the first character is a letter
		if (!std::isalpha(source.front())) {
			return std::nullopt;
		}

		// Check if the rest of the characters are are letters(numbers are not allowed)
		for (size_t x = 1; x < source.size(); x++) {
			if (!std::isalpha(source.at(x))) {
				return std::nullopt;
			}
		}

		// Check if the keyword is a valid keyword
		if (source.starts_with("let")) {
			auto nextChar = source.substr(3).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(LET, KEYWORD, "let", 0, 3);
			} 
		} else if (source.starts_with("var")) {
			auto nextChar = source.substr(3).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(VAR, KEYWORD, "var", 0, 3);
			}
		} else if (source.starts_with("fn")) {
			auto nextChar = source.substr(2).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(FUNC, KEYWORD, "fn", 0, 2);
			}
		} else if (source.starts_with("class")) {
			auto nextChar = source.substr(5).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(CLASS, KEYWORD, "class", 0, 5);
			}
		} else if (source.starts_with("contract")) {
			auto nextChar = source.substr(6).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(CONTRACT, KEYWORD, "struct", 0, 6);
			}
		} else if (source.starts_with("struct")) {
			auto nextChar = source.substr(6).front();
			if (!std::isdigit(nextChar) && !std::isalpha(nextChar)) {
				return MAKE_TOKEN(STRUCT, KEYWORD, "struct", 0, 6);
			}
		}
			
		return std::nullopt;
	}
}