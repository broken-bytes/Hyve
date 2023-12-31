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
        uint64_t _currentColumnStart;
        uint64_t _currentColumnEnd;

        // Returns the content and whether this is a string literal
        std::tuple<std::string, bool, uint64_t, uint64_t> NextToken(std::string& source);
        // Processes a string
        std::optional<std::tuple<std::string, uint64_t, uint64_t>> ProcessStringLiteral(std::string& source);
        std::optional<std::tuple<std::string, uint64_t, uint64_t>> ProcessNumberLiteral(std::string& source);
        std::optional<std::tuple<std::string, uint64_t, uint64_t>> ProcessLineBreak(std::string& source);
    };
}