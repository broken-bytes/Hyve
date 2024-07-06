#pragma once

namespace Hyve::Lexer {
    enum class HTokenFamily {
        KEYWORD,
        LITERAL,
        OPERATOR,
        SPECIAL,
        GROUPING,
        IDENTIFIER_FAMILY,
        ERROR_FAMILY,
        UNKNOWN
    };

    enum class HTokenType {
        // Special Tokens
        ERROR,
        END_OF_FILE,
        INVALID,

        // Keywords
        // Types
        ACTOR,
        CLASS,
        CONTRACT,
        ENUM,
        MODULE,
        PROTOTYPE,
        SELF,
        STRUCT,

        // Access Modifiers
        FILEPRIVATE,
        INTERNAL,
        OPEN,
        PRIVATE,
        PUBLIC,

        // Variables & Constants
        LET,
        VAR,

        // Control Flow
        ASYNC,
        AWAIT,
        BREAK,
        CATCH,
        CONTINUE,
        DEFER,
        DO,
        ELSE,
        FINALLY,
        FOR,
        FUNC,
        GUARD,
        IF,
        IMPORT,
        IN,
        INIT,
        OF,
        RETURN,
        THROW,
        THROWS,
        TRY,
        UNTIL,
        WHEN,
        WHILE,
        WITH,
        YIELD,

        // Operators
        // Arithmetic
        ASSIGNMENT,
        DIVIDE,
        DIVIDE_ASSIGN,
        MINUS,
        MINUS_ASSIGN,
        MODULO,
        MOD_ASSIGN,
        MULTIPLY,
        MULTIPLY_ASSIGN,
        PLUS,
        PLUS_ASSIGN,
        INCREMENT,
        DECREMENT,

        // Bitwise
        BIT_AND,
        BIT_INVERSE,
        BIT_LSHIFT,
        BIT_NEGATE,
        BIT_OR,
        BIT_RSHIFT,
        XOR,

        // Logical
        AND,
        NOT,
        OR,

        // Comparison
        EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,
        NOT_EQUAL,

        // Other Operators
        ANNOTATION,
        ARROW,
        AS,
        BINDING,
        COLON,
        COMMA,
        DOT,
        FORCE_OPTIONAL,
        NAME_OVERRIDE,
        OPTIONAL,
        PIPE,
        HARD_UNWRAP,
        SOFT_UNWRAP,

        // Literals
        BOOLEAN,
        FALSE,
        FLOAT,
        INTEGER,
        NULL_LITERAL,
        STRING,
        TRUE,

        // Brackets
        BRACKET_LEFT,
        BRACKET_RIGHT,
        CURLY_LEFT,
        CURLY_RIGHT,
        PAREN_LEFT,
        PAREN_RIGHT,

        // Identifiers and Comments
        CAPTURED,
        IDENTIFIER,
        LINEBREAK,
        MULTI_LINE_COMMENT,
    };

    constexpr HTokenFamily GetFamily(HTokenType type) {
        using enum HTokenType;
        using enum HTokenFamily;

        switch (type) {
        case IDENTIFIER:
            return IDENTIFIER_FAMILY;
        case BOOLEAN:
        case FLOAT:
        case INTEGER:
        case NULL_LITERAL:
        case STRING:
            return HTokenFamily::LITERAL;
        case BIT_AND:
        case BIT_INVERSE:
        case BIT_LSHIFT:
        case BIT_NEGATE:
        case BIT_OR:
        case BIT_RSHIFT:
        case AND:
        case ARROW:
        case ASSIGNMENT:
        case DIVIDE:
        case DIVIDE_ASSIGN:
        case DOT:
        case EQUAL:
        case GREATER:
        case GREATER_EQUAL:
        case LESS:
        case LESS_EQUAL:
        case MINUS:
        case MINUS_ASSIGN:
        case MODULO:
        case MOD_ASSIGN:
        case MULTIPLY:
        case MULTIPLY_ASSIGN:
        case NOT_EQUAL:
        case PLUS:
        case PLUS_ASSIGN:
        case PIPE:
        case OR:
        case XOR:
            return OPERATOR;
        case BRACKET_LEFT:
        case BRACKET_RIGHT:
        case CURLY_LEFT:
        case CURLY_RIGHT:
        case PAREN_LEFT:
        case PAREN_RIGHT:
            return GROUPING;
        case ACTOR:
        case ASYNC:
        case AWAIT:
        case BREAK:
        case CATCH:
        case CLASS:
        case CONTINUE:
        case DO:
        case ELSE:
        case ENUM:
        case FOR:
        case FILEPRIVATE:
        case FINALLY:
        case FUNC:
        case IF:
        case IMPORT:
        case IN:
        case INIT:
        case LET:
        case OF:
        case OPEN:
        case PRIVATE:
        case PUBLIC:
        case RETURN:
        case SELF:
        case STRUCT:
        case THROW:
        case THROWS:
        case TRY:
        case UNTIL:
        case VAR:
        case WHEN:
        case WHILE:
        case YIELD:
            return KEYWORD;
        case COMMA:
        case COLON:
            return SPECIAL;
        default:
            return UNKNOWN;
        }
    }
}