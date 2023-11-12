#pragma once

namespace Hyve::Lexer {
    enum class HTokenFamily {
        IDENTIFIER,
        KEYWORD,
        LITERAL,
        OPERATOR,
        SPECIAL,
        COMMENT,
        ERROR,
        LINEBREAK,
        END_OF_FILE
    };

    enum class HTokenType {
        ERROR,
        IDENTIFIER,
        // Types
        ACTOR, // actor
        CLASS, // actor
        PROTOCOL, // protocol
        PROTOTYPE, // prototype
        STRUCT, // struct
        OPEN, // open

        // Variables
        VAR, // var
        LET, // let

        // COMPARISON
        NOT_EQUAl, // !=
        EQUAL, // ==,
        LESS, // <
        LESS_EQUAL, // <=
        GREATER, // >
        GREATER_EQUAL, // >=

        // ARITHMETIC
        ASSIGNMENT, // =
        PLUS, // +
        MINUS, // -
        MULTIPLY, // *
        DIVIDE, // /
        MODULO, // %
        AND, // &&
        OR, // ||
        NOT, // !
        BIT_AND, // &
        BIT_OR, // |
        BIT_INVERSE, // ~
        BIT_NEGATE, //
        BIT_LSHIFT, // <<
        BIT_RSHIFT, // >>
        PLUS_ASSIGN, // +=
        MINUS_ASSIGN, // -=
        MULTIPLY_ASSIGN, // *=
        DIVIDE_ASSIGN, // /=,
        MOD_ASSIGN, // %=

        // FLOW
        IF, // if
        ELSE, // else
        WHEN, // when
        FUNC, // func
        DEFER, // defer
        DO, // do
        CATCH, // catch
        TRY, // try
        FINALLY, // finally
        UNTIL, // until
        GUARD, // guard
        CAPTURED, // captured
        TASK, // task
        AWAIT, // await
        ASYNC, // async,
        THROW, // throw
        THROWS, // throws
        ARROW, // ->
        OPTIONAL, // ?
        FORCE_OPTIONAL, // ?

        // OTHER OPERATORS
        DOT, // .
        COLON, // :,
        COMMA, // ,
        ANNOTATION, // @Bla
        BINDING, // $
        NAME_OVERRIDE, // ``
        PIPE, // |

        // BRACKETS
        LBRACKET, // (
        RBRACKET, // )
        LCBRACKET, // {
        RCBRACKET, // }
        LSBRACKET, // [
        RSBRACKET, // ]

        // CONSTANTS
        NUM, // 23
        STRING, // "test",
        COMMENT, // //
        MULTI_LINE_COMMENT, // */ ... /*
        LINEBREAK, // \n,
        END_OF_FILE, // the end of a file
        INVALID // Not a proper token
    };
}