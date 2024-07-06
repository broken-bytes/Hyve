#include "lexer/processors/HOperatorProcessor.hxx"
#include "lexer/HTokenOperators.hxx"

namespace Hyve::Lexer {
	std::optional<HToken> HOperatorProcessor::Process(std::string_view source) {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.empty()) {
			return std::nullopt;
		}

		// An operator cannot start with a letter or digit
		if (std::isalnum(source[0])) {
			return std::nullopt;
		}

		// Operators may be more than one character long.
		// Get the count until the first non-operator character
		size_t count = 0;

		while (count < source.size() && IsOperator(source.at(count))) {
			count++;
		}

		auto operatorStr = std::string(source.substr(0, count));

		if(auto compound = ProcessCompoundOperator(operatorStr); compound.has_value()) {
			return compound;
		}

		if(auto comparison = ProcessComparisonOperator(operatorStr); comparison.has_value()) {
			return comparison;
		}

		if(auto logical = ProcessLogicalOperator(operatorStr); logical.has_value()) {
			return logical;
		}

		if (auto special = ProcessSpecialOperator(operatorStr); special.has_value()) {
			return special;
		}

		if (auto math = ProcessMathOperator(operatorStr); math.has_value()) {
			return math;
		}

		if(auto bitwise = ProcessBitwiseOperator(operatorStr); bitwise.has_value()) {
			return bitwise;
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessCompoundOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_ADD_ASSIGN)) {
			return MAKE_TOKEN(PLUS_ASSIGN, OPERATOR_ADD_ASSIGN);
		}

		if (source.starts_with(OPERATOR_SUB_ASSIGN)) {
			return MAKE_TOKEN(MINUS_ASSIGN, OPERATOR_SUB_ASSIGN);
		}

		if (source.starts_with(OPERATOR_MUL_ASSIGN)) {
			return MAKE_TOKEN(MULTIPLY_ASSIGN, OPERATOR_MUL_ASSIGN);
		}

		if (source.starts_with(OPERATOR_DIV_ASSIGN)) {
			return MAKE_TOKEN(DIVIDE_ASSIGN, OPERATOR_DIV_ASSIGN);
		}

		if (source.starts_with(OPERATOR_MOD_ASSIGN)) {
			return MAKE_TOKEN(MOD_ASSIGN, OPERATOR_MOD_ASSIGN);
		}

		// Ensure that the assignment operator is not confused with the equality operator
		if (source.starts_with(OPERATOR_ASSIGN) && !source.starts_with(OPERATOR_EQUAL)) {
			return MAKE_TOKEN(ASSIGNMENT, OPERATOR_ASSIGN);
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessMathOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_ADD)) {
			return MAKE_TOKEN(PLUS, OPERATOR_ADD);
		}

		if (source.starts_with(OPERATOR_SUB)) {
			return MAKE_TOKEN(MINUS, OPERATOR_SUB);
		}

		if (source.starts_with(OPERATOR_MUL)) {
			return MAKE_TOKEN(MULTIPLY, OPERATOR_MUL);
		}

		if (source.starts_with(OPERATOR_DIV)) {
			return MAKE_TOKEN(DIVIDE, OPERATOR_DIV);
		}

		if (source.starts_with(OPERATOR_MOD)) {
			return MAKE_TOKEN(MODULO, OPERATOR_MOD);
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessComparisonOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_EQUAL)) {
			return MAKE_TOKEN(EQUAL, OPERATOR_EQUAL);
		}

		if (source.starts_with(OPERATOR_NOT_EQUAL)) {
			return MAKE_TOKEN(NOT_EQUAL, OPERATOR_NOT_EQUAL);
		}

		if (source.starts_with(OPERATOR_LESS_EQUAL)) {
			return MAKE_TOKEN(LESS_EQUAL, OPERATOR_LESS_EQUAL);
		}

		if (source.starts_with(OPERATOR_GREATER_EQUAL)) {
			return MAKE_TOKEN(GREATER_EQUAL, OPERATOR_GREATER_EQUAL);
		}

		if (source.starts_with(OPERATOR_LESS)) {
			return MAKE_TOKEN(LESS, OPERATOR_LESS);
		}

		if (source.starts_with(OPERATOR_GREATER)) {
			return MAKE_TOKEN(GREATER, OPERATOR_GREATER);
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessLogicalOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_AND_AND)) {
			return MAKE_TOKEN(AND, OPERATOR_AND_AND);
		}

		if (source.starts_with(OPERATOR_OR_OR)) {
			return MAKE_TOKEN(OR, OPERATOR_OR_OR);
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessSpecialOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_INC)) {
			return MAKE_TOKEN(INCREMENT, OPERATOR_INC);
		}

		if (source.starts_with(OPERATOR_DEC)) {
			return MAKE_TOKEN(DECREMENT, OPERATOR_DEC);
		}

		if (source.starts_with(OPERATOR_ARROW)) {
			return MAKE_TOKEN(ARROW, OPERATOR_ARROW);
		}

		if (source.starts_with(OPERATOR_NOT)) {
			return MAKE_TOKEN(NOT, OPERATOR_NOT);
		}

		if (source.starts_with(OPERATOR_DOT)) {
			return MAKE_TOKEN(DOT, OPERATOR_DOT);
		}

		return std::nullopt;
	}

	std::optional<HToken> HOperatorProcessor::ProcessBitwiseOperator(std::string_view source) const {
		using enum HTokenType;
		using enum HTokenFamily;
		using namespace Operators;

		if (source.starts_with(OPERATOR_SHIFT_LEFT)) {
			return MAKE_TOKEN(BIT_LSHIFT, OPERATOR_SHIFT_LEFT);
		}

		if (source.starts_with(OPERATOR_SHIFT_RIGHT)) {
			return MAKE_TOKEN(BIT_RSHIFT, OPERATOR_SHIFT_RIGHT);
		}

		if (source.starts_with(OPERATOR_AND)) {
			return MAKE_TOKEN(BIT_AND, OPERATOR_AND);
		}

		if (source.starts_with(OPERATOR_OR)) {
			return MAKE_TOKEN(BIT_OR, OPERATOR_OR);
		}

		if (source.starts_with(OPERATOR_XOR)) {
			return MAKE_TOKEN(XOR, OPERATOR_XOR);
		}

		return std::nullopt;
	}
}