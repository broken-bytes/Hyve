#pragma once

#include "lexer/HProcessor.hxx"
#include <optional>
#include <string_view>

namespace Hyve::Lexer {
	struct HToken;

	class HControlFlowProcessor final : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HControlFlowProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}