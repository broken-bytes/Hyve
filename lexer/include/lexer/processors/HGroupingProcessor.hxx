#pragma once

#include "lexer/HProcessor.hxx"
#include <string_view>

namespace Hyve::Lexer {
	class HGroupingProcessor final : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HGroupingProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}