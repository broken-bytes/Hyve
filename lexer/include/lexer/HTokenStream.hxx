#pragma once

#include "lexer/HToken.hxx"
#include <queue>

namespace Hyve::Lexer {
    class HTokenStream {
        public:
        HTokenStream(std::queue<HToken>& tokens);
        HToken Peek();
        const HToken Take();

        private:
        std::queue<HToken> _tokens;
    };
}