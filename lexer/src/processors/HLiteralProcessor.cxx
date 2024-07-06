#include "lexer/processors/HLiteralProcessor.hxx"
#include "lexer/processors/HNumberProcessor.hxx"
#include "lexer/HToken.hxx"

namespace Hyve::Lexer {
	HLiteralProcessor::HLiteralProcessor(
		std::shared_ptr<HNumberProcessor> numberProcessor
	) : HProcessor(), _numberProcessor(numberProcessor) {}

	std::optional<HToken> HLiteralProcessor::Process(std::string_view source) {
		// Check if the first character is ". If it is, then it is a string literal
		// If it is a number, then it is a numeric literal
		// Otherwise we need to check if it is a boolean or null literal
		// If it is none of the above, then it is not a literal
		if (auto numericLiteral = ProcessNumericLiteral(source); numericLiteral.has_value()) {
			return numericLiteral;
		}
		else if (auto booleanLiteral = ProcessBooleanLiteral(source); booleanLiteral.has_value()) {
			return booleanLiteral;
		}
		else if (auto stringLiteral = ProcessStringLiteral(source); stringLiteral.has_value()) {
			return stringLiteral;
		}
		else if (auto nullLiteral = ProcessNullLiteral(source); nullLiteral.has_value()) {
			return nullLiteral;
		} else {
			return std::nullopt;
		}
	}

	std::optional<HToken> HLiteralProcessor::ProcessNumericLiteral(std::string_view source) {
		return _numberProcessor->Process(source);
	}

	std::optional<HToken> HLiteralProcessor::ProcessBooleanLiteral(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;

		if(source.starts_with("true")) {
			return MAKE_TOKEN(TRUE, LITERAL, "true", 0, 4);
		} else if(source.starts_with("false")) {
			return MAKE_TOKEN(FALSE, LITERAL, "false", 0, 5);
		}

		return std::nullopt;
	}

	std::optional<HToken> HLiteralProcessor::ProcessStringLiteral(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;

		bool isStringLiteral = false;

		if (source.starts_with("\"")) {
			isStringLiteral = true;
		}

		// Parse until we find the closing quote
		if (isStringLiteral) {
			std::string literalValue;
			size_t literalLength = 0;

			for (size_t i = 1; i < source.size(); i++) {
				if (source[i] == '"') {
					literalLength = i + 1;
					break;
				}
				literalValue += source[i];
			}

			if (literalLength == 0) {
				return std::nullopt;
			}

			return MAKE_TOKEN(STRING, LITERAL, literalValue, 0, literalLength);
		}

		return std::nullopt;
	}

	std::optional<HToken> HLiteralProcessor::ProcessNullLiteral(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;

		if(source.starts_with("null")) {
			return MAKE_TOKEN(NULL, LITERAL, "null", 0, 4);
		}

		return std::nullopt;
	}
}