#pragma once

#include "lexer/HProcessor.hxx"
#include <cstdbool>
#include <optional>
#include <string_view>

namespace Hyve::Lexer {
	struct HToken;

	class HKeywordProcessor final : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HKeywordProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}