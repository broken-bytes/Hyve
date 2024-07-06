#pragma once

#include "lexer/HProcessor.hxx"
#include <optional>

namespace Hyve::Lexer {
	struct HToken;

	class HKeywordProcessor : public HProcessor {
	public:
		HKeywordProcessor() = default;
		~HKeywordProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}