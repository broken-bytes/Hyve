#include "lexer/processors/HPunctuationProcessor.hxx"
#include "lexer/HTokenSpecials.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HPunctuationProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Specials;
		// Check if the first character is a punctuation
		// What is a punctuation?
		// , ( ) [ ] { }
		// Everything else is an operator or not covered by this processor

		if (source.empty()) {
			return std::nullopt;
		}

		// No punctuation starts with a letter or a number
		if (std::isalnum(source.front())) {
			return std::nullopt;
		}

		// Check if the first character is a punctuation
		if (CheckMatchingSequence(source, SPECIAL_COMMA)) {
			return MAKE_TOKEN(COMMA, ",");
		}

		return std::nullopt;
	}
}