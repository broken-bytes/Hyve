#pragma once

#include "lexer/HProcessor.hxx"
#include <optional>
#include <string_view>

namespace Hyve::Lexer {
	struct HToken;

	class HSpecialProcessor : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HSpecialProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}