#include "lexer/HLexer.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenKeywords.hxx"
#include "lexer/HTokenSymbols.hxx"
#include "lexer/HTokenType.hxx"
#include "lexer/HTokenStream.hxx"
#include <exception>
#include <regex>
#include <stdexcept>

namespace Hyve::Lexer {
    std::string identifierStr = "[a-zA-Z_]+[a-zA-Z0-9_]*";
    std::regex identifierRegex(identifierStr);

    [[nodiscard]] HTokenType TryGetKeyword(const std::string& source) {
        if(source.contains(Keywords::KEYWORD_ACTOR)) {
            return HTokenType::ACTOR;
        }

        if(source.contains(Keywords::KEYWORD_CAPTURED)) {
            return HTokenType::CAPTURED;
        }

        if(source.contains(Keywords::KEYWORD_CATCH)) {
            return HTokenType::CATCH;
        }

        if(source.contains(Keywords::KEYWORD_CLASS)) {
            return HTokenType::CLASS;
        }

        if(source.contains(Keywords::KEYWORD_DEFER)) {
            return HTokenType::DEFER;
        }

        if(source.contains(Keywords::KEYWORD_DO)) {
            return HTokenType::DO;
        }

        if(source.contains(Keywords::KEYWORD_ELSE)) {
            return HTokenType::ELSE;
        }

        if(source.contains(Keywords::KEYWORD_FUNC)) {
            return HTokenType::FUNC;
        }

        if(source.contains(Keywords::KEYWORD_IF)) {
            return HTokenType::IF;
        }

        if(source.contains(Keywords::KEYWORD_LET)) {
            return HTokenType::LET;
        }

        if(source.contains(Keywords::KEYWORD_PROTOCOL)) {
            return HTokenType::PROTOCOL;
        }

        if(source.contains(Keywords::KEYWORD_PROTOTYPE)) {
            return HTokenType::PROTOTYPE;
        }

        if(source.contains(Keywords::KEYWORD_STRUCT)) {
            return HTokenType::STRUCT;
        }

        if(source.contains(Keywords::KEYWORD_WHEN)) {
            return HTokenType::WHEN;
        }

        if(source.contains(Keywords::KEYWORD_THROW)) {
            return HTokenType::THROW;
        }

        if(source.contains(Keywords::KEYWORD_THROWS)) {
            return HTokenType::THROWS;
        }

        if(source.contains(Keywords::KEYWORD_TRY)) {
            return HTokenType::TRY;
        }

        if(source.contains(Keywords::KEYWORD_UNTIL)) {
            return HTokenType::UNTIL;
        }

        if(source.contains(Keywords::KEYWORD_VAR)) {
            return HTokenType::VAR;
        }

        if(source.contains(Keywords::KEYWORD_OPEN)) {
            return HTokenType::OPEN;
        }

        return HTokenType::INVALID;
    }

    [[nodiscard]] HTokenType TryGetIdentifier(const std::string& source) {
        std::sregex_iterator it(source.begin(), source.end(), identifierRegex);
        std::sregex_iterator end;

        while (it != end) {
            std::smatch match = *it;
            ++it;

            return HTokenType::IDENTIFIER;
        }

        return HTokenType::INVALID;
    }


    [[nodiscard]] HTokenType TryGetOperator(const std::string& source) {
        if(source == Symbols::SYMBOL_ASSIGN) {
            return HTokenType::ASSIGNMENT;
        }

        if(source == Symbols::SYMBOL_PLUS) {
            return HTokenType::PLUS;
        }

        if(source == Symbols::SYMBOL_MINUS) {
            return HTokenType::MINUS;
        }

        if(source == Symbols::SYMBOL_MULTIPLY) {
            return HTokenType::MULTIPLY;
        }

        if(source == Symbols::SYMBOL_DIVIDE) {
            return HTokenType::DIVIDE;
        }

        if(source == Symbols::SYMBOL_MODULO) {
            return HTokenType::MODULO;
        }

        if(source == Symbols::SYMBOL_EQUAL) {
            return HTokenType::EQUAL;
        }

        if(source == Symbols::SYMBOL_NOT_EQUAL) {
            return HTokenType::NOT_EQUAl;
        }

        if(source == Symbols::SYMBOL_GREATER_THAN) {
            return HTokenType::GREATER;
        }

        if(source == Symbols::SYMBOL_LESS_THAN) {
            return HTokenType::LESS;
        }

        if(source == Symbols::SYMBOL_GREATER_THAN_OR_EQUAL) {
            return HTokenType::GREATER_EQUAL;
        }

        if(source == Symbols::SYMBOL_LESS_THAN_OR_EQUAL) {
            return HTokenType::LESS_EQUAL;
        }

        if(source == Symbols::SYMBOL_AND) {
            return HTokenType::AND;
        }

        if(source == Symbols::SYMBOL_OR) {
            return HTokenType::OR;
        }

        if(source == Symbols::SYMBOL_NOT) {
            return HTokenType::NOT;
        }

        if(source == Symbols::SYMBOL_BITWISE_AND) {
            return HTokenType::BIT_AND;
        }

        if(source == Symbols::SYMBOL_BITWISE_OR) {
            return HTokenType::BIT_OR;
        }

        if(source == Symbols::SYMBOL_BITWISE_XOR) {
            return HTokenType::BIT_OR;
        }

        if(source == Symbols::SYMBOL_BITWISE_NOT) {
            return HTokenType::BIT_INVERSE;
        }

        if(source == Symbols::SYMBOL_BITWISE_LEFT_SHIFT) {
            return HTokenType::BIT_LSHIFT;
        }

        if(source == Symbols::SYMBOL_BITWISE_RIGHT_SHIFT) {
            return HTokenType::BIT_RSHIFT;
        }

        if(source == Symbols::SYMBOL_PLUS_ASSIGN) {
            return HTokenType::PLUS_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MINUS_ASSIGN) {
            return HTokenType::MINUS_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MULTIPLY_ASSIGN) {
            return HTokenType::MULTIPLY_ASSIGN;
        }

        if(source == Symbols::SYMBOL_DIVIDE_ASSIGN) {
            return HTokenType::DIVIDE_ASSIGN;
        }

        if(source == Symbols::SYMBOL_MODULO_ASSIGN) {
            return HTokenType::MOD_ASSIGN;
        }

        if(source == Symbols::SYMBOL_ARROW) {
            return HTokenType::ARROW;
        }

        if(source == Symbols::SYMBOL_QUESTION_MARK) {
            return HTokenType::OPTIONAL;
        }

        if(source == Symbols::EXCLAMATION_MARK) {
            return HTokenType::FORCE_OPTIONAL;
        }

        if(source == Symbols::SYMBOL_AT) {
            return HTokenType::ANNOTATION;
        }

        if(source == Symbols::SYMBOL_DOLLAR) {
            return HTokenType::BINDING;
        }

        if(source == Symbols::SYMBOL_BACKTICK) {
            return HTokenType::NAME_OVERRIDE;
        }

        if(source == Symbols::SYMBOL_QUOTE) {
            return HTokenType::STRING;
        }

        if(source == Symbols::SYMBOL_PIPE) {
            return HTokenType::PIPE;
        }

        return HTokenType::INVALID;
    }

    HTokenType TryGetSpecial(const std::string& source)  {
        if(source == Symbols::SYMBOL_LEFT_BRACKET) {
            return HTokenType::LBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_BRACKET) {
            return HTokenType::RBRACKET;
        }

        if(source == Symbols::SYMBOL_LEFT_CURLY_BRACKET) {
            return HTokenType::LCBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_CURLY_BRACKET) {
            return HTokenType::RCBRACKET;
        }

        if(source == Symbols::SYMBOL_LEFT_SQUARE_BRACKET) {
            return HTokenType::LSBRACKET;
        }

        if(source == Symbols::SYMBOL_RIGHT_SQUARE_BRACKET) {
            return HTokenType::RSBRACKET;
        }

        if(source == Symbols::SYMBOL_COMMA) {
            return HTokenType::COMMA;
        }

        if(source == Symbols::SYMBOL_DOT) {
            return HTokenType::DOT;
        }

        if(source == Symbols::SYMBOL_COLON) {
            return HTokenType::COLON;
        }

        if(source == Symbols::SYMBOL_QUOTE) {
            return HTokenType::STRING;
        }

        if(source == Symbols::SYMBOL_ARROW) {
            return HTokenType::ARROW;
        }

        return HTokenType::INVALID;
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
                throw std::runtime_error("Unterminated string literal");
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

                throw std::runtime_error("Undefined symbol");
            }
        }

        return { next , false };
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
                tokens.push(HToken{
                        .Family = HTokenFamily::ERROR,
                        .Type = HTokenType::ERROR,
                        .Value = error.what(),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });
                _state = LexerState::NONE;
            }

            // If we are in string mode the next sequence is guaranteed to be a string
            if(std::get<1>(currentToken)) {
                _state = LexerState::NONE;
                tokens.push(HToken{
                        .Family = HTokenFamily::LITERAL,
                        .Type = HTokenType::STRING,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });

                continue;
            }

            // Line break
            if(std::get<0>(currentToken)[0] == '\n') {
                tokens.push(HToken{
                        .Family = HTokenFamily::LINEBREAK,
                        .Type = HTokenType::LINEBREAK,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });

                continue;
            }

            currentType = TryGetKeyword(std::get<0>(currentToken));

            if (currentType != HTokenType::INVALID) {
                _state = LexerState::KEYWORD;
                tokens.push(HToken{
                        .Family = HTokenFamily::KEYWORD,
                        .Type = currentType,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });

                continue;
            }

            currentType = TryGetIdentifier(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                _state = LexerState::NONE;
                tokens.push(HToken{
                        .Family = HTokenFamily::IDENTIFIER,
                        .Type = HTokenType::IDENTIFIER,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });

                continue;
            }

            currentType = TryGetOperator(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                _state = LexerState::NONE;
                tokens.push(HToken{
                        .Family = HTokenFamily::OPERATOR,
                        .Type = currentType,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });
                continue;
            }

            currentType = TryGetSpecial(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                // Edge case, if a string is detected, swap the lexer to string mode
                if(currentType == HTokenType::STRING) {
                    _state = LexerState::STRINGLITERAL;
                    continue;
                }
                tokens.push(HToken{
                        .Family = HTokenFamily::OPERATOR,
                        .Type = currentType,
                        .Value = std::get<0>(currentToken),
                        .Line = _currentLine,
                        .Column = _currentColumn
                });
                continue;
            }

        } while(!content.empty());

        return tokens;
    }
}