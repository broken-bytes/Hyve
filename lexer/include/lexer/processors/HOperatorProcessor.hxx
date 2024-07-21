#pragma once

#include "lexer/HProcessor.hxx"
#include <string_view>

namespace Hyve::Lexer {
	class HOperatorProcessor final : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HOperatorProcessor() final = default;

		std::optional<HToken> Process(std::string_view source) final;

	private:
		std::optional<HToken> ProcessCompoundOperator(std::string_view source) const;
		/**
		* @brief Process a math operator
		* @param source The source code
		* @return The token if the operator is found
		* @note Call this after all 2+ character operators have been processed
		*/
		std::optional<HToken> ProcessMathOperator(std::string_view source) const;
		std::optional<HToken> ProcessComparisonOperator(std::string_view source) const;
		std::optional<HToken> ProcessLogicalOperator(std::string_view source) const;
		std::optional<HToken> ProcessSpecialOperator(std::string_view source) const;
		/**
		* @brief Process a bitwise operator
		* @param source The source code
		* @return The token if the operator is found
		* @note Call this after all 2+ character operators have been processed
		*/
		std::optional<HToken> ProcessBitwiseOperator(std::string_view source) const;
	};
}