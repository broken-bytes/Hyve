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

		// Check two character operators first so they aren't shadowed by one character operators (e.g. == vs =)
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

		if(source.starts_with(OPERATOR_AND_AND)) {
			return MAKE_TOKEN(AND, OPERATOR_AND_AND);
		}

		if(source.starts_with(OPERATOR_OR_OR)) {
			return MAKE_TOKEN(OR, OPERATOR_OR_OR);
		}

		if(source.starts_with(OPERATOR_EQUAL)) {
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

		if (source.starts_with(OPERATOR_INC)) {
			return MAKE_TOKEN(INCREMENT, OPERATOR_INC);
		}

		if (source.starts_with(OPERATOR_DEC)) {
			return MAKE_TOKEN(DECREMENT, OPERATOR_DEC);
		}

		if (source.starts_with(OPERATOR_ARROW)) {
			return MAKE_TOKEN(ARROW, OPERATOR_ARROW);
		}

		if (source.starts_with(OPERATOR_SHIFT_LEFT)) {
			return MAKE_TOKEN(BIT_LSHIFT, OPERATOR_SHIFT_LEFT);
		}

		if (source.starts_with(OPERATOR_SHIFT_RIGHT)) {
			return MAKE_TOKEN(BIT_RSHIFT, OPERATOR_SHIFT_RIGHT);
		}

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

		if (source.starts_with(OPERATOR_ASSIGN)) {
			return MAKE_TOKEN(ASSIGNMENT, OPERATOR_ASSIGN);
		}

		if (source.starts_with(OPERATOR_NOT)) {
			return MAKE_TOKEN(NOT, OPERATOR_NOT);
		}

		if (source.starts_with(OPERATOR_LESS)) {
			return MAKE_TOKEN(LESS, OPERATOR_LESS);
		}

		if (source.starts_with(OPERATOR_GREATER)) {
			return MAKE_TOKEN(GREATER, OPERATOR_GREATER);
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