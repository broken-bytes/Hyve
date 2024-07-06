#pragma

#include "lexer/HProcessor.hxx"
#include <memory>
#include <optional>

namespace Hyve::Lexer {
	class HNumberProcessor;
	class HLiteralProcessor : public HProcessor {
	public:
		HLiteralProcessor(std::shared_ptr<HNumberProcessor> numberProcessor);
		~HLiteralProcessor() final = default;

		std::optional<HToken> Process(std::string_view) final;

	private:
		std::optional<HToken> ProcessNumericLiteral(std::string_view source);
		std::optional<HToken> ProcessBooleanLiteral(std::string_view source);
		std::optional<HToken> ProcessStringLiteral(std::string_view source);
		std::optional<HToken> ProcessNullLiteral(std::string_view source);
		void HandleError(std::string_view source, std::string_view message);

		std::shared_ptr<HNumberProcessor> _numberProcessor;
	};
}