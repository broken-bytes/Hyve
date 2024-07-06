#pragma

#include "lexer/HProcessor.hxx"
#include <optional>

namespace Hyve::Lexer {
	class HNumberProcessor : public HProcessor {
	public:
		using HProcessor::HProcessor;
		~HNumberProcessor() final = default;

		std::optional<HToken> Process(std::string_view) final;

	private:
		std::optional<HToken> ProcessInteger(std::string_view source) const;
		std::optional<HToken> ProcessFloat(std::string_view source) const;
		std::optional<HToken> ProcessHex(std::string_view source) const;
		std::optional<HToken> ProcessBinary(std::string_view source) const;
	};
}