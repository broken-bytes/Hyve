#include "lexer/HLexer.hxx"
#include "lexer/HLexerError.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenKeywords.hxx"
#include "lexer/HTokenSymbols.hxx"
#include "lexer/HTokenType.hxx"
#include <exception>
#include <regex>
#include <stdexcept>

namespace Hyve::Lexer {
    const std::string identifierStr = "[a-zA-Z_]+[a-zA-Z0-9_]*";
    const std::regex identifierRegex(identifierStr);

    [[nodiscard]] HTokenType TryGetKeyword(const std::string& source) {
        using enum Hyve::Lexer::HTokenType;
        if(source == Keywords::KEYWORD_ACTOR) {
            return ACTOR;
        }

        if(source == Keywords::KEYWORD_CAPTURED) {
            return CAPTURED;
        }

        if(source == Keywords::KEYWORD_CATCH) {
            return CATCH;
        }

        if(source == Keywords::KEYWORD_CLASS) {
            return CLASS;
        }

        if(source == Keywords::KEYWORD_DEFER) {
            return DEFER;
        }

        if(source == Keywords::KEYWORD_DO) {
            return DO;
        }

        if(source == Keywords::KEYWORD_ELSE) {
            return ELSE;
        }

        if(source == Keywords::KEYWORD_FUNC) {
            return FUNC;
        }

        if(source == Keywords::KEYWORD_IF) {
            return IF;
        }

        if(source == Keywords::KEYWORD_LET) {
            return LET;
        }

        if(source == Keywords::KEYWORD_PROTOCOL) {
            return PROTOCOL;
        }

        if(source == Keywords::KEYWORD_PROTOTYPE) {
            return PROTOTYPE;
        }

        if(source == Keywords::KEYWORD_STRUCT) {
            return STRUCT;
        }

        if(source == Keywords::KEYWORD_WHEN) {
            return WHEN;
        }

        if(source == Keywords::KEYWORD_THROW) {
            return THROW;
        }

        if(source == Keywords::KEYWORD_THROWS) {
            return THROWS;
        }

        if(source == Keywords::KEYWORD_TRY) {
            return TRY;
        }

        if(source == Keywords::KEYWORD_UNTIL) {
            return UNTIL;
        }

        if(source == Keywords::KEYWORD_VAR) {
            return VAR;
        }

        if(source == Keywords::KEYWORD_OPEN) {
            return OPEN;
        }

        return INVALID;
    }

    [[nodiscard]] HTokenType TryGetIdentifier(const std::string_view source) {
        std::string sourceStr(source.begin(), source.end()); // Convert to std::string
        std::sregex_iterator it(sourceStr.begin(), sourceStr.end(), identifierRegex);


        if (std::sregex_iterator end; it != end) {
            std::smatch match = *it;
            ++it;

            return HTokenType::IDENTIFIER;
        }

        return HTokenType::INVALID;
    }


    [[nodiscard]] HTokenType TryGetOperator(const std::string_view source) {
        using enum Hyve::Lexer::HTokenType;
        if(source == Symbols::SYMBOL_ASSIGN) {
            return ASSIGNMENT;
        }

        if(source == Symbols::SYMBOL_PLUS) {
            return PLUS;
        }

        if(source == Symbols::SYMBOL_MINUS) {
            return MINUS;
        }

        if(source == Symbols::SYMBOL_MULTIPLY) {
            return MULTIPLY;
        }

        if(source == Symbols::SYMBOL_DIVIDE) {
            return DIVIDE;
        }

        if(source == Symbols::SYMBOL_MODULO) {
            return MODULO;
        }

        if(source == Symbols::SYMBOL_EQUAL) {
            return EQUAL;
        }

        if(source == Symbols::SYMBOL_NOT_EQUAL) {
            return NOT_EQUAl;
        }

        if(source == Symbols::SYMBOL_GREATER_THAN) {
            return GREATER;
        }

        if(source == Symbols::SYMBOL_LESS_THAN) {
            return LESS;
        }

        if(source == Symbols::SYMBOL_GREATER_THAN_OR_EQUAL) {
            return GREATER_EQUAL;
        }

        if(source == Symbols::SYMBOL_LESS_THAN_OR_EQUAL) {
            return LESS_EQUAL;
        }

        if(source == Symbols::SYMBOL_AND) {
            return AND;
        }

        if(source == Symbols::SYMBOL_OR) {
            return OR;
        }

        if(source == Symbols::SYMBOL_NOT) {
            return NOT;
        }

        if(source == Symbols::SYMBOL_BITWISE_AND) {
            return BIT_AND;
        }

        if(source == Symbols::SYMBOL_BITWISE_OR) {
            return BIT_OR;
        }

        if(source == Symbols::SYMBOL_BITWISE_XOR) {
            return BIT_OR;
        }

        if(source == Symbols::SYMBOL_BITWISE_NOT) {
            return BIT_INVERSE;
        }

        if(source == Symbols::SYMBOL_BITWISE_LEFT_SHIFT) {
            return BIT_LSHIFT;
        }

        if(source == Symbols::SYMBOL_BITWISE_RIGHT_SHIFT) {
            return BIT_RSHIFT;
        }

        if(source == Symbols::SYMBOL_PLUS_ASSIGN) {
            return PLUS_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MINUS_ASSIGN) {
            return MINUS_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MULTIPLY_ASSIGN) {
            return MULTIPLY_ASSIGN;
        }

        if(source == Symbols::SYMBOL_DIVIDE_ASSIGN) {
            return DIVIDE_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MODULO_ASSIGN) {
            return MOD_ASSIGN;
        }

        if(source == Symbols::SYMBOL_ARROW) {
            return ARROW;
        }

        if(source == Symbols::SYMBOL_QUESTION_MARK) {
            return OPTIONAL;
        }

        if(source == Symbols::EXCLAMATION_MARK) {
            return FORCE_OPTIONAL;
        }

        if(source == Symbols::SYMBOL_AT) {
            return ANNOTATION;
        }

        if(source == Symbols::SYMBOL_DOLLAR) {
            return BINDING;
        }

        if(source == Symbols::SYMBOL_BACKTICK) {
            return NAME_OVERRIDE;
        }

        if(source == Symbols::SYMBOL_QUOTE) {
            return STRING;
        }

        if(source == Symbols::SYMBOL_PIPE) {
            return PIPE;
        }

        return INVALID;
    }

    HTokenType TryGetSpecial(const std::string_view source)  {
        using enum Hyve::Lexer::HTokenType;
        if(source == Symbols::SYMBOL_LEFT_BRACKET) {
            return LBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_BRACKET) {
            return RBRACKET;
        }

        if(source == Symbols::SYMBOL_LEFT_CURLY_BRACKET) {
            return LCBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_CURLY_BRACKET) {
            return RCBRACKET;
        }

        if(source == Symbols::SYMBOL_LEFT_SQUARE_BRACKET) {
            return LSBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_SQUARE_BRACKET) {
            return RSBRACKET;
        }

        if(source == Symbols::SYMBOL_COMMA) {
            return COMMA;
        }

        if(source == Symbols::SYMBOL_DOT) {
            return DOT;
        }

        if(source == Symbols::SYMBOL_COLON) {
            return COLON;
        }

        if(source == Symbols::SYMBOL_QUOTE) {
            return STRING;
        }

        if(source == Symbols::SYMBOL_ARROW) {
            return ARROW;
        }

        if(source == Symbols::SYMBOL_COMMENT) {
            return COMMENT;
        }

        if(source == Symbols::SYMBOL_MULTILINE_COMMENT_BEGIN) {
            return MULTI_LINE_COMMENT;
        }

        return INVALID;
    }

    void RemoveComment(std::string& source, bool multiLine) {
        auto len = source.length();

        if(multiLine) {
            for(int offset = 0; offset < source.length(); offset++) {
                if(source.substr(offset, 2) == Symbols::SYMBOL_MULTILINE_COMMENT_END) {
                    source.erase(0, offset + 1);
                    return;
                }
            }
        } else {
            for(int offset = 0; offset < source.length(); offset++) {
                printf("Char: %c\n", source[offset]);
                if (source[offset] == '\n') {
                    source.erase(0, offset + 1);
                    return;
                }
            }
        }
    }

    // Gets the next string from current point until next whitespace and removes the whitespace
    std::tuple<std::string, bool> HLexer::NextToken(std::string& source) {
        std::string next;

        // State handling:
        // - If we have a string, we need to find the closing quote
        // - If we started with anything that is not a symbol, we go on until we hit one
        // If we have a symbol, we peed the next char as well to make sure it is not a different symbol
        // Since keywords would match the identifier regex as well if we didn't catch them earlier, we can reuse the regex here

        // First check if we have a string
        if(source[0] == Symbols::SYMBOL_QUOTE[0]) {
            _state = LexerState::STRINGLITERAL;

            // Edge case: Empty string, thus check if the next char is a quote as well
            if(source[1] == Symbols::SYMBOL_QUOTE[0]) {
                _state = LexerState::NONE;
                source.erase(0, 2);
                return { "" , true };
            }

            // Go over the whole string until we hit a quote or EOF, which would result in an error
            for(int x = 1; x < source.length(); x++) {
                if(source[x] == Symbols::SYMBOL_QUOTE[0]) {
                    _state = LexerState::NONE;
                    next = source.substr(1, x);
                    source.erase(0, x + 1);
                    return { next , true };
                }
            }

            if(_state == LexerState::STRINGLITERAL) {
                source.erase(0, source.length());
                throw HLexerError("Unterminated string literal");
            }
        }

        // If not, check for linebreaks before anything else
        if(source[0] == '\n') {
            source.erase(0, 1);
            return { "\n" , false };
        }

        for(int offset = 0; offset < source.length(); offset++) {
            // If we start with alphanumeric or underscore, we have a proper literal and not a symbol
            if (std::isalnum(source[offset]) || source[offset] == Symbols::SYMBOL_UNDERSCORE[0]) {
                if (_state == LexerState::SYMBOL) {
                    next = source.substr(0, offset);
                    source.erase(0, offset);
                    return { next , false };
                }
                _state = LexerState::VALUE;
            }
            // We have some sort of whitespace or
            else if (std::isspace(source[offset])) {
                // Edge case 1: If the line starts with a whitespace(not \n), remove it immediately
                if(offset == 0) {
                    if(source[0] != '\n') {
                        source.erase(0, 1);
                        return NextToken(source);
                    } else {
                        source.erase(0, 1);
                        return { "\n", false };
                    }
                }
                // If we hit a whitespace, we automatically end the Token if not in a string literal.
                next = source.substr(0, offset);
                // Edge case 2: If the character is a linebreak, we don't remove it from the source str as linebreaks are tokens
                source.erase(0, offset + (source[offset] == '\n' ? 0 : 1));
                return { next , false };
            }
                // We have symbol, now we need to check if it is a two or one chars symbol
            else {
                if (_state == LexerState::VALUE) {
                    next = source.substr(0, offset);
                    source.erase(0, offset);
                    return { next , false };
                }

                // Symbols can have two characters max, thus we check if it is a two char symbol first, else return one char
                _state = LexerState::SYMBOL;

                bool isTwoCharacters = false;

                if(TryGetSpecial(source.substr(0, offset + 2)) != HTokenType::INVALID) {
                    isTwoCharacters = true;
                }

                if(TryGetOperator(source.substr(0, offset + 2)) != HTokenType::INVALID) {
                    isTwoCharacters = true;
                }

                if(isTwoCharacters) {
                    next = source.substr(0, 2);
                    source.erase(0, 2);
                    _state = LexerState::NONE;

                    // Extra check: Remove all characters until comments are ended if a comment is detected
                    if(next == Symbols::SYMBOL_COMMENT) {
                        RemoveComment(source, false);
                        continue;
                    }

                    if(next == Symbols::SYMBOL_MULTILINE_COMMENT_BEGIN) {
                        RemoveComment(source, true);
                        continue;
                    }

                    return { next, false };
                } else {
                    if(TryGetSpecial(source.substr(0, offset + 1)) != HTokenType::INVALID) {
                        next = source.substr(0, 1);
                        source.erase(0, 1);
                        _state = LexerState::NONE;

                        return { next, false };
                    }

                    if(TryGetOperator(source.substr(0, offset + 1)) != HTokenType::INVALID) {
                        next = source.substr(0, 1);
                        source.erase(0, 1);
                        _state = LexerState::NONE;

                        return { next, false };
                    }
                }

                source.erase(0, 1);
                _state = LexerState::NONE;

                throw HLexerError("Undefined symbol");
            }
        }

        return { next , false };
    }

    void PushToken(
            HTokenType type,
            HTokenFamily family,
            std::string_view value,
            uint64_t line,
            uint64_t column,
            std::queue<HToken>& queue) {
        queue.push(HToken{
                .Family = family,
                .Type = type,
                .Value = std::string(value),
                .Line = line,
                .Column = column
        });
    }

    HLexer::HLexer() = default;

    std::queue<HToken> HLexer::Tokenize(std::string stream) {
        std::queue<HToken> tokens = {};

        _currentLine = 1;
        _currentColumn = 1;
        _state = LexerState::NONE;

        std::string content = std::move(stream);
        // Use the first two chars for context. Code must start with a keyword, which is 2 chars min
        std::tuple<std::string, bool> currentToken;

        _state = LexerState::NONE;

        auto currentType = HTokenType::INVALID;

        do {
            try {
                currentToken = NextToken(content);
            } catch(std::exception& error) {
                PushToken(HTokenType::ERROR, HTokenFamily::ERROR, error.what(), _currentLine, _currentColumn, tokens);
                _state = LexerState::NONE;
            }

            // If we are in string mode the next sequence is guaranteed to be a string
            if(std::get<1>(currentToken)) {
                _state = LexerState::NONE;
                PushToken(
                        HTokenType::STRING,
                        HTokenFamily::LITERAL,
                        std::get<0>(currentToken),
                                _currentLine,
                                _currentColumn, tokens
                                );
                continue;
            }

            // Line break
            if(std::get<0>(currentToken)[0] == '\n') {
                PushToken(
                        HTokenType::LINEBREAK,
                        HTokenFamily::LINEBREAK,
                        std::get<0>(currentToken),
                        _currentLine,
                        _currentColumn, tokens
                );

                continue;
            }

            currentType = TryGetKeyword(std::get<0>(currentToken));

            if (currentType != HTokenType::INVALID) {
                _state = LexerState::KEYWORD;
                PushToken(
                        currentType,
                        HTokenFamily::KEYWORD,
                        std::get<0>(currentToken),
                        _currentLine,
                        _currentColumn, tokens
                );

                continue;
            }

            currentType = TryGetIdentifier(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                _state = LexerState::NONE;
                PushToken(
                        HTokenType::IDENTIFIER,
                        HTokenFamily::IDENTIFIER,
                        std::get<0>(currentToken),
                        _currentLine,
                        _currentColumn, tokens
                );

                continue;
            }

            currentType = TryGetOperator(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                _state = LexerState::NONE;
                PushToken(
                        currentType,
                        HTokenFamily::OPERATOR,
                        std::get<0>(currentToken),
                        _currentLine,
                        _currentColumn, tokens
                );

                continue;
            }

            currentType = TryGetSpecial(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                // Edge case, if a string is detected, swap the lexer to string mode
                if(currentType == HTokenType::STRING) {
                    _state = LexerState::STRINGLITERAL;
                    continue;
                }
                PushToken(
                        currentType,
                        HTokenFamily::OPERATOR,
                        std::get<0>(currentToken),
                        _currentLine,
                        _currentColumn, tokens
                );
                continue;
            }

        } while(!content.empty());

        PushToken(
                HTokenType::END_OF_FILE,
                HTokenFamily::END_OF_FILE,
                "",
                _currentLine,
                _currentColumn, tokens
        );

        return tokens;
    }
}