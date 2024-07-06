#include "lexer/processors/HControlFlowProcessor.hxx"
#include "lexer/HToken.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HControlFlowProcessor::Process(std::string_view source) {
		using enum HTokenFamily;
		using enum HTokenType;

		// No control flow keyword can be less than 2 characters(if, do)
		if (source.size() < 2) {
			return std::nullopt;
		}

		if(source == "if") {
			return MAKE_TOKEN(IF, KEYWORD, "if", 0, 2);
		}

		if (source == "else") {
			return MAKE_TOKEN(ELSE, KEYWORD, "else", 0, 4);
		}

		if (source == "do") {
			return MAKE_TOKEN(DO, KEYWORD, "do", 0, 2);
		}

		if (source == "while") {
			return MAKE_TOKEN(WHILE, KEYWORD, "while", 0, 5);
		}

		if (source == "for") {
			return MAKE_TOKEN(FOR, KEYWORD, "for", 0, 3);
		}

		if (source == "break") {
			return MAKE_TOKEN(BREAK, KEYWORD, "break", 0, 5);
		}

		if (source == "continue") {
			return MAKE_TOKEN(CONTINUE, KEYWORD, "continue", 0, 8);
		}

		if(source == "return") {
			return MAKE_TOKEN(RETURN, KEYWORD, "return", 0, 6);
		}

		if (source == "when") {
			return MAKE_TOKEN(WHEN, KEYWORD, "switch", 0, 6);
		}

		if (source == "try") {
			return MAKE_TOKEN(TRY, KEYWORD, "try", 0, 3);
		}

		return std::nullopt;
	}
}