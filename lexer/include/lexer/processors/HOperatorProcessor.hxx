#pragma once

#include "lexer/HProcessor.hxx"
#include <string_view>

namespace Hyve::Lexer {
	class HOperatorProcessor : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HOperatorProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;
	};
}