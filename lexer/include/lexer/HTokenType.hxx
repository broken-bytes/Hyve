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
        MODULE, // module
        STRUCT, // struct
        SELF, // self

        // Access levels
        PUBLIC, // public
        INTERNAL, // internal
        PRIVATE, // private
        FILEPRIVATE, // fileprivate
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
        XOR, // ^
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
        INIT, // init
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
        WHILE, // while
        FOR, // for
        IN, // in
        OF, // of
        WITH, // with
        YIELD, // yield
        RETURN, // return
        IMPORT, // import

        // OTHER OPERATORS
        AS, // as
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

        // Literals
        TRUE, // true,
        FALSE, // false,
        NUM, // 23
        STRING, // "test",
        COMMENT, // //
        NULL_LITERAL, // null
        MULTI_LINE_COMMENT, // */ ... /*
        LINEBREAK, // \n,
        END_OF_FILE, // the end of a file
        INVALID // Not a proper token
    };
}