#include "lexer/processors/HControlFlowProcessor.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenKeywords.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HControlFlowProcessor::Process(std::string_view source) {
		using enum HTokenFamily;
		using enum HTokenType;
		using namespace Keywords;

		// No control flow keyword can be less than 2 characters(if, do)
		if (source.size() < 2) {
			return std::nullopt;
		}

		if(CheckMatchingSequence(source, KEYWORD_IF)) {
			return MAKE_TOKEN(IF, KEYWORD_IF);
		}

		if (CheckMatchingSequence(source, KEYWORD_ELSE)) {
			return MAKE_TOKEN(ELSE, KEYWORD_ELSE);
		}

		if (CheckMatchingSequence(source, KEYWORD_DO)) {
			return MAKE_TOKEN(DO, KEYWORD_DO);
		}

		if (CheckMatchingSequence(source, KEYWORD_WHILE)) {
			return MAKE_TOKEN(WHILE, KEYWORD_WHILE);
		}

		if (CheckMatchingSequence(source, KEYWORD_FOR)) {
			return MAKE_TOKEN(FOR, KEYWORD_FOR);
		}

		if (CheckMatchingSequence(source, KEYWORD_BREAK)) {
			return MAKE_TOKEN(BREAK, KEYWORD_BREAK);
		}

		if (CheckMatchingSequence(source, KEYWORD_CONTINUE)) {
			return MAKE_TOKEN(CONTINUE, KEYWORD_CONTINUE);
		}

		if(CheckMatchingSequence(source, KEYWORD_RETURN)) {
			return MAKE_TOKEN(RETURN, KEYWORD_RETURN);
		}

		if (CheckMatchingSequence(source, KEYWORD_WHEN)) {
			return MAKE_TOKEN(WHEN, KEYWORD_WHEN);
		}

		if (CheckMatchingSequence(source, KEYWORD_TRY)) {
			return MAKE_TOKEN(TRY, KEYWORD_TRY);
		}

		return std::nullopt;
	}
}