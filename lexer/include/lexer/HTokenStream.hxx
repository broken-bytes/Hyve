#pragma once

#include "lexer/HToken.hxx"
#include <stdexcept>
#include <iterator>
#include <vector>

namespace Hyve::Lexer {
    class HTokenStream {
        class TokenStreamError : public std::runtime_error {
            using std::runtime_error::runtime_error;
		};
    public:
        using iterator = std::vector<HToken>::iterator;
        using const_iterator = std::vector<HToken>::const_iterator;

        explicit HTokenStream(const std::vector<HToken>& tokens) : _tokens(tokens) {
            
        }

        // Push a token onto the back of the stream
        void PushBack(const HToken& token) {
            _tokens.push_back(token);
        }

        // Consume (and remove) the token at the current position
        HToken Consume() {
            if (_currentPosition >= _tokens.size()) {
                // Return the EOF token, no matter if it exists or not
                return HToken { Lexer::HTokenFamily::UNKNOWN, Lexer::HTokenType::END_OF_FILE };
            }
            auto token = _tokens[_currentPosition];
            _currentPosition++;
            
            return token;
        }

        HToken Consume(Lexer::HTokenType type) {
            if (_currentPosition >= _tokens.size()) {
                return HToken { Lexer::HTokenFamily::UNKNOWN, Lexer::HTokenType::END_OF_FILE };
            }
            auto token = _tokens[_currentPosition];
            _currentPosition++;

            if (token.Type != type) {
				throw TokenStreamError("Unexpected token");
			}

            return token;
        }

        // Peek at the next token without consuming it
        HToken Peek() const {
            if (_currentPosition >= _tokens.size()) {
                // Throw an error
                return HToken{ Lexer::HTokenFamily::UNKNOWN, Lexer::HTokenType::END_OF_FILE };
            }

            return _tokens[_currentPosition];
        }

        std::vector<HToken> Peek(uint64_t count) const {
            if (_currentPosition + count >= _tokens.size()) {
                // Throw an error
                auto first = Peek();

                return { first, HToken { Lexer::HTokenFamily::UNKNOWN, Lexer::HTokenType::END_OF_FILE } };
            }

            return std::vector<HToken>(
                _tokens.begin() + _currentPosition,
                _tokens.begin() + _currentPosition + count
            );
        }

        /// <summary>
        /// Consumes tokens until a non-linebreak token is found, which is only peaked, not consumed
        /// </summary>
        /// <returns></returns>
        HToken PeekUntilNonLineBreak() {
			size_t i = _currentPosition;
			while (i < _tokens.size()) {
				if (_tokens[i].Type != Lexer::HTokenType::LINEBREAK) {
                    _currentPosition = i;
					return _tokens[i];
				}
                
                i++;
			}

			throw TokenStreamError("Peeked past end of token stream");
		}

        // Iterator interface for iteration over the stream
        iterator Begin() { return _tokens.begin(); }
        iterator End() { return _tokens.end(); }
        const_iterator Begin() const { return _tokens.begin(); }
        const_iterator End() const { return _tokens.end(); }

    private:
        std::vector<HToken> _tokens;        // Store the tokens
        size_t _currentPosition = 0;        // Current position for consumption
    };
}