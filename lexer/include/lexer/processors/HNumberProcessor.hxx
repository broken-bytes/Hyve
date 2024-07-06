#pragma

#include "lexer/HProcessor.hxx"
#include <optional>

namespace Hyve::Lexer {
	class HNumberProcessor : public HProcessor {
	public:
		HNumberProcessor() : HProcessor() {}
		~HNumberProcessor() final = default;

		std::optional<HToken> Process(std::string_view) final;

	private:
		std::optional<HToken> ProcessInteger(std::string_view source);
		std::optional<HToken> ProcessFloat(std::string_view source);
		std::optional<HToken> ProcessHex(std::string_view source);
		std::optional<HToken> ProcessBinary(std::string_view source);
		void HandleError(std::string_view source, std::string_view message);
	};
}