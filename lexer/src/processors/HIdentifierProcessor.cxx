#include "lexer/processors/HIdentifierProcessor.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenType.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HIdentifierProcessor::Process(std::string_view source) {
		if (source.empty()) {
			return std::nullopt;
		}

		if (!std::isalpha(source.front()) && source.front() != '_') {
			return std::nullopt;
		}

		size_t i = 1;
		while (i < source.size() && (std::isalnum(source.at(i)) || source.at(i) == '_')) {
			i++;
		}

		auto token = std::string(source.substr(0, i));

		return MAKE_TOKEN(HTokenType::IDENTIFIER, token);
	}

}