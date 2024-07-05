#pragma once

namespace Hyve::Lexer {
    enum class HTokenFamily {
        KEYWORD,
        LITERAL,
        OPERATOR,
        SPECIAL,
        UNKNOWN
    };

    enum class HTokenType {
        ERROR,
        IDENTIFIER,
        // Types
        ACTOR,
        CLASS,
        PROTOCOL,
        PROTOTYPE,
        MODULE,
        STRUCT,
        SELF,
        ENUM,

        // Access levels
        PUBLIC,
        INTERNAL,
        PRIVATE,
        FILEPRIVATE,
        OPEN,

        // Variables
        VAR,
        LET,

        // COMPARISON
        NOT_EQUAl,
        EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,

        // ARITHMETIC
        ASSIGNMENT,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE, 
        MODULO, 
        AND,
        OR,
        NOT,
        XOR,
        BIT_AND,
        BIT_OR, 
        BIT_INVERSE,
        BIT_NEGATE,
        BIT_LSHIFT,
        BIT_RSHIFT,
        PLUS_ASSIGN,
        MINUS_ASSIGN,
        MULTIPLY_ASSIGN,
        DIVIDE_ASSIGN,
        MOD_ASSIGN,

        // FLOW
        IF,
        ELSE,
        WHEN,
        INIT,
        FUNC,
        DEFER,
        DO,
        CATCH,
        TRY,
        FINALLY,
        UNTIL,
        GUARD,
        CAPTURED,
        TASK,
        AWAIT,
        ASYNC,
        THROW,
        THROWS,
        ARROW,
        OPTIONAL,
        FORCE_OPTIONAL,
        WHILE,
        FOR,
        IN,
        OF,
        WITH,
        YIELD,
        RETURN,
        IMPORT,

        // OTHER OPERATORS
        AS,
        DOT,
        COLON,
        COMMA,
        ANNOTATION,
        BINDING,
        NAME_OVERRIDE,
        PIPE,

        // BRACKETS
        LBRACKET,
        RBRACKET,
        LCBRACKET,
        RCBRACKET,
        LSBRACKET,
        RSBRACKET,

        // Literals
        TRUE,
        FALSE,
        NUM,
        STRING,
        NULL_LITERAL,
        MULTI_LINE_COMMENT,
        LINEBREAK,
        END_OF_FILE,
        INVALID
    };
}