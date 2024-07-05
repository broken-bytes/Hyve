#pragma once

#include <stdexcept>
#include <string>

namespace Hyve::Lexer {
    class HLexerError : public std::runtime_error {
        public:
            using std::runtime_error::runtime_error;
    };
}