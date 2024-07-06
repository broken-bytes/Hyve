#pragma

#include "lexer/HProcessor.hxx"
#include <memory>
#include <optional>

namespace Hyve::Lexer {
	class HNumberProcessor;
	class HLiteralProcessor : public HProcessor {
	public:
		explicit HLiteralProcessor(std::shared_ptr<HNumberProcessor> numberProcessor);
		~HLiteralProcessor() final = default;

		std::optional<HToken> Process(std::string_view) final;

	private:
		std::optional<HToken> ProcessNumericLiteral(std::string_view source) const;
		std::optional<HToken> ProcessBooleanLiteral(std::string_view source) const;
		std::optional<HToken> ProcessStringLiteral(std::string_view source) const;
		std::optional<HToken> ProcessNullLiteral(std::string_view source) const;

		std::shared_ptr<HNumberProcessor> _numberProcessor;
	};
}