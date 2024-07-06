#include "lexer/processors/HGroupingProcessor.hxx"
#include "lexer/HTokenGroupings.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HGroupingProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Groupings;
		// Check if the first character is a punctuation
		// What is a grouping symbol?
		// ( ) [ ] { }
		// Everything else is not covered by this processor

		if (source.empty()) {
			return std::nullopt;
		}

		// No punctuation starts with a letter or a number
		if (std::isalnum(source.front())) {
			return std::nullopt;
		}

		if (CheckMatchingSequence(source, GROUPING_PAREN_LEFT)) {
			return MAKE_TOKEN(PAREN_LEFT, GROUPING_PAREN_LEFT);
		}

		if (CheckMatchingSequence(source, GROUPING_PAREN_RIGHT)) {
			return MAKE_TOKEN(PAREN_RIGHT, GROUPING_PAREN_RIGHT);
		}

		if (CheckMatchingSequence(source, GROUPING_BRACKET_LEFT)) {
			return MAKE_TOKEN(BRACKET_LEFT, GROUPING_BRACKET_LEFT);
		}

		if (CheckMatchingSequence(source, GROUPING_BRACKET_RIGHT)) {
			return MAKE_TOKEN(BRACKET_RIGHT, GROUPING_BRACKET_RIGHT);
		}

		if (CheckMatchingSequence(source, GROUPING_CURLY_LEFT)) {
			return MAKE_TOKEN(CURLY_LEFT, GROUPING_CURLY_LEFT);
		}

		if (CheckMatchingSequence(source, GROUPING_CURLY_RIGHT)) {
			return MAKE_TOKEN(CURLY_RIGHT, GROUPING_CURLY_RIGHT);
		}

		return std::nullopt;
	}
}