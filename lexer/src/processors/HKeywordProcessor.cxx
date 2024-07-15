#include "lexer/processors/HKeywordProcessor.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenKeywords.hxx"
#include <optional>
#include <string_view>

namespace Hyve::Lexer {
	std::optional<HToken> HKeywordProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;
        using namespace Keywords;

		// No keyword is less than 2 characters
		if (source.size() < 2) {
			return std::nullopt;
		}

		// Check if the first character is a letter
		if (!std::isalpha(source.front())) {
			return std::nullopt;
		}

		// Check if the keyword is a valid keyword
        if (CheckMatchingSequence(source, KEYWORD_ALLOC)) {
            return MAKE_TOKEN(ALLOC, KEYWORD_ALLOC);
        } else if (CheckMatchingSequence(source, KEYWORD_ASYNC)) {
            return MAKE_TOKEN(ASYNC, KEYWORD_ASYNC);
        }
        else if (CheckMatchingSequence(source, KEYWORD_AWAIT)) {
            return MAKE_TOKEN(AWAIT, KEYWORD_AWAIT);
        }
        else if (CheckMatchingSequence(source, KEYWORD_CONTRACT)) {
            return MAKE_TOKEN(CONTRACT, KEYWORD_CONTRACT);
        }
        else if (CheckMatchingSequence(source, KEYWORD_DEALLOC)) {
            return MAKE_TOKEN(DEALLOC, KEYWORD_DEALLOC);
        }
        else if (CheckMatchingSequence(source, KEYWORD_FUNC)) {
            return MAKE_TOKEN(FUNC, KEYWORD_FUNC);
        }
        else if (CheckMatchingSequence(source, KEYWORD_LET)) {
            return MAKE_TOKEN(LET, KEYWORD_LET);
        }
        else if (CheckMatchingSequence(source, KEYWORD_STRUCT)) {
            return MAKE_TOKEN(STRUCT, KEYWORD_STRUCT);
        }
        else if (CheckMatchingSequence(source, KEYWORD_VAR)) {
            return MAKE_TOKEN(VAR, KEYWORD_VAR);
        }
        else if (CheckMatchingSequence(source, KEYWORD_MODULE)) {
            return MAKE_TOKEN(MODULE, KEYWORD_MODULE);
        }
        else if (CheckMatchingSequence(source, KEYWORD_IMPORT)) {
            return MAKE_TOKEN(IMPORT, KEYWORD_IMPORT);
        }
        else if (CheckMatchingSequence(source, KEYWORD_PUBLIC)) {
			return MAKE_TOKEN(PUBLIC, KEYWORD_PUBLIC);
        }
        else if (CheckMatchingSequence(source, KEYWORD_PRIVATE)) {
            return MAKE_TOKEN(PRIVATE, KEYWORD_PRIVATE);
        }
        else if (CheckMatchingSequence(source, KEYWORD_INIT)) {
            return MAKE_TOKEN(INIT, KEYWORD_INIT);
        }
			
		return std::nullopt;
	}
}