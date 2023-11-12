#pragma once

#include "lexer/HToken.hxx"
#include <queue>
#include <string>

namespace Hyve::Lexer {
    enum class LexerState {
        NONE,
        KEYWORD,
        IDENTIFIER,
        VALUE,
        STRINGLITERAL,
        SYMBOL,
        COMMENT,
        MULTILINE_COMMENT
    };

    class HLexer {
        public:
        HLexer();
        [[nodiscard]] std::queue<HToken> Tokenize(std::string stream, std::string& fileName);

    private:
        LexerState _state;
        uint64_t _currentLine;
        uint64_t _currentColumn;

        // Returns the content and whether this is a string literal
        std::tuple<std::string, bool> NextToken(std::string& source);
    };
}