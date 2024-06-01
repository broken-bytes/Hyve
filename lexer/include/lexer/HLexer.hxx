#pragma once

#include "lexer/HToken.hxx"
#include <queue>
#include <vector>

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
        [[nodiscard]] std::vector<HToken> Tokenize(std::string stream, const std::string& fileName);

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
        bool NextIsLineBreak(std::string& source);
        void RemoveComment(std::string& source, bool multiLine, uint64_t& currentLine, uint64_t& currentColumn);
    };
}