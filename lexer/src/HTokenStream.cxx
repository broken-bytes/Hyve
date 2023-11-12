#include "lexer/HTokenStream.hxx"
#include "lexer/HToken.hxx"

#include <queue>

namespace Hyve::Lexer {
    HTokenStream::HTokenStream(std::queue<HToken>& tokens) {
        this->_tokens = tokens;
    }

    HToken HTokenStream::Peek() {
        return _tokens.front();
    }

    const HToken HTokenStream::Take() {
        return _tokens.front();
    }
}