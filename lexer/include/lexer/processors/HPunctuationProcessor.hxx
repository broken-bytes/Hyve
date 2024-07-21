#pragma once

#include "lexer/HProcessor.hxx"
#include <string_view>

namespace Hyve::Lexer {
	class HPunctuationProcessor final : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HPunctuationProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}