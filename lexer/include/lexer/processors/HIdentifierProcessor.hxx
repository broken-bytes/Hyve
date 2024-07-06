#pragma once

#include "lexer/HProcessor.hxx"
#include <string_view>

namespace Hyve::Lexer {
	class HIdentifierProcessor : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HIdentifierProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}