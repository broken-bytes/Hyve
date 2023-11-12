#pragma once

#include <stdexcept>
#include <string>

namespace Hyve::Lexer {
    class HLexerError : public std::runtime_error {
        public:
        explicit HLexerError(const std::string& message) : std::runtime_error(message) { }
    };
}