#pragma once

#include "lexer/processors/HSpecialProcessor.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenType.hxx"
#include "lexer/HTokenSpecials.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HSpecialProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using namespace Specials;

		if (source.empty()) {
			return std::nullopt;
		}

		if (source.front() == '\n') {
			return MAKE_TOKEN(LINEBREAK, "\n");
		}

		if(source.starts_with(SPECIAL_HARD_UNWRAP)) {
			return MAKE_TOKEN(HARD_UNWRAP, SPECIAL_HARD_UNWRAP);
		}

		if(source.starts_with(SPECIAL_SOFT_UNWRAP)) {
			return MAKE_TOKEN(SOFT_UNWRAP, SPECIAL_SOFT_UNWRAP);
		}

		if(source.starts_with(SPECIAL_COLON)) {
			return MAKE_TOKEN(COLON, SPECIAL_COLON);
		}

		return std::nullopt;
	};
}