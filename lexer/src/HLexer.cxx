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

        if (source == Keywords::KEYWORD_MODULE) {
            return MODULE;
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

        if(source == Keywords::KEYWORD_WHILE) {
            return WHILE;
        }

        if(source == Keywords::KEYWORD_WITH) {
            return WITH;
        }

        if(source == Keywords::KEYWORD_YIELD) {
            return YIELD;
        }

        if(source == Keywords::KEYWORD_RETURN) {
            return RETURN;
        }

        if(source == Keywords::KEYWORD_IMPORT) {
            return IMPORT;
        }

        if(source == Keywords::KEYWORD_AS) {
            return AS;
        }

        if(source == Keywords::KEYWORD_SELF) {
            return SELF;
        }

        if(source == Keywords::KEYWORD_TASK) {
            return TASK;
        }

        if(source == Keywords::KEYWORD_NULL) {
            return NULL_LITERAL;
        }

        if(source == Keywords::KEYWORD_INIT) {
            return INIT;
        }

        if(source == Keywords::KEYWORD_PUBLIC) {
			return PUBLIC;
		}

        if(source == Keywords::KEYWORD_INTERNAL) {
			return INTERNAL;
		}

        if(source == Keywords::KEYWORD_PRIVATE) {
            return PRIVATE;
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

    void Erase(std::string& source, size_t count) {
        for(int x = 0; x < count; x++) {
            if(std::isspace(source[x])) {
                continue;
            }

        }

        source.erase(0, count);
    }

    void HLexer::RemoveComment(
        std::string& source, 
        bool multiLine, 
        uint64_t& currentLine, 
        uint64_t& currentColumn
    ) {
        auto len = source.length();

        if(multiLine) {
            for(int offset = 0; offset < source.length(); offset++) {
                if(source.substr(offset, 2) == Symbols::SYMBOL_MULTILINE_COMMENT_END) {
                    Erase(source, 2);
                    return;
                } else if(source[offset] == '\n') {
                    currentLine++;
                }
            }
        } else {
            for(int offset = 0; offset < source.length(); offset++) {
                if(NextIsLineBreak(source)) {
					currentLine++;
					return;
                }
                else {
                    Erase(source, 1);
                }
            }
        }
    }

    std::optional<std::tuple<std::string, uint64_t, uint64_t>> HLexer::ProcessStringLiteral(std::string& source) {
        std::string next;

        if(source[0] == Symbols::SYMBOL_QUOTE[0]) {
            _state = LexerState::STRINGLITERAL;

            // Edge case: Empty string, thus check if the next char is a quote as well
            if(source[1] == Symbols::SYMBOL_QUOTE[0]) {
                _state = LexerState::NONE;
                Erase(source, 2);
                auto result = std::tuple<std::string, uint64_t, uint64_t> {
                        next, _currentColumnStart, _currentColumnStart + 1
                };

                _currentColumnStart = _currentColumnStart + 2;

                return result;
            }

            // Go over the whole string until we hit a quote or EOF, which would result in an error
            for(int x = 1; x < source.length(); x++) {
                if(source[x] == Symbols::SYMBOL_QUOTE[0]) {
                    _state = LexerState::NONE;
                    next = source.substr(1, x);
                    Erase(source, x + 1);
                    auto result = std::tuple<std::string, uint64_t, uint64_t> {
                            next, _currentColumnStart, _currentColumnStart + x
                    };
                    _currentColumnStart = _currentColumnStart + x + 1;

                    return result;
                }
            }

            if(_state == LexerState::STRINGLITERAL) {
                Erase(source, source.length());
                throw HLexerError("Unterminated string literal");
            }
        }

        return std::nullopt;
    }

    std::optional<std::tuple<std::string, uint64_t, uint64_t>> HLexer::ProcessNumberLiteral(std::string& source) {
        if(std::isdigit(static_cast<int>(source[0]))) {
            std::string next;
            bool isDoubleLiteral = false;
            bool isBinOrHex = false;

            // Number literal, keep going until we reach whitespace, or any character
            for(int offset = 0; offset < source.length(); offset++) {
                // We hit a guaranteed literal end via whitespace
                if (std::isspace(static_cast<int>(source[offset]))) {
                    next = source.substr(0, offset);
                    Erase(source, 1);

                    auto result = std::tuple<std::string, uint64_t, uint64_t> {
                        next, _currentColumnStart, _currentColumnStart + offset
                    };
                    _currentColumnStart = _currentColumnStart + offset;

                    return result;
                }

                // If we receive a numeric character, we are still in the number literal
                if(std::isdigit(source[offset])) {
					continue;
				}

                // If we receive a dot we are in a double literal
                if(!std::isdigit(source[offset]) && source[offset] == '.') {
                    if(isBinOrHex) {
                        Erase(source, 1);
                        _currentColumnStart = _currentColumnStart + offset + 1;
                        throw HLexerError("Binary or hex numbers cannot be doubles");
                    }
                    isDoubleLiteral = true;
                    continue;
                }
                // Only the second character is allowed to be x or b, but only if first char is 0
                if (offset == 1  && (source[1] == 'b' || source[1] == 'x')) {
                    isBinOrHex = true;
                    continue;
                }

                // Invalid number literal
                if(std::isalpha(source[offset])) {
                    Erase(source, 1);
                    _currentColumnStart = _currentColumnStart + offset + 1;

                    if(!isDoubleLiteral) {
                        throw HLexerError("Invalid integer literal");
                    }

                    throw HLexerError("Invalid double literal");
                }

                next = source.substr(0, offset);
            }
        }

        return std::nullopt;
    }

    bool HLexer::NextIsLineBreak(std::string& source) {
        // First check if we have two characters left, so we can check for \r\n or \n\r and remove both
        bool checkForBoth = source.length() >= 2;

        if (checkForBoth) {
            if (source[0] == '\r' && source[1] == '\n') {
                return true;
            }

            if (source[0] == '\n' && source[1] == '\r') {
                return true;
            }
        }
        else {
            if (source[0] == '\n') {
                return true;
            }
        }

        return false;
    }

    std::optional<std::tuple<std::string, uint64_t, uint64_t>> HLexer::ProcessLineBreak(std::string& source) {
        // First check if we have two characters left, so we can check for \r\n or \n\r and remove both
        bool checkForBoth = source.length() >= 2;

        if(checkForBoth) {
			if(source[0] == '\r' && source[1] == '\n') {
				Erase(source, 2);
				auto result = std::tuple<std::string, uint64_t, uint64_t> {
						"\n", _currentColumnStart, _currentColumnStart
				};
				_currentColumnStart = 1;
				_currentLine++;

				return result;
			}

			if(source[0] == '\n' && source[1] == '\r') {
				Erase(source, 2);
				auto result = std::tuple<std::string, uint64_t, uint64_t> {
						"\n", _currentColumnStart, _currentColumnStart
				};
				_currentColumnStart = 1;
				_currentLine++;

				return result;
			}
        } else {
           if(source[0] == '\n') {
			   Erase(source, 1);
			   auto result = std::tuple<std::string, uint64_t, uint64_t> {
					   "\n", _currentColumnStart, _currentColumnStart
			   };
			   _currentColumnStart = 1;
			   _currentLine++;

			   return result;
		   }
       }

        return std::nullopt;
    }

    // Gets the next string from current point until next whitespace and removes the whitespace
    // content, string, start, end
    std::tuple<std::string, bool, uint64_t, uint64_t> HLexer::NextToken(std::string& source) {
        std::string next;

        // State handling:
        // - If we have a string, we need to find the closing quote
        // - If we started with anything that is not a symbol, we go on until we hit one
        // If we have a symbol, we peed the next char as well to make sure it is not a different symbol
        // Since keywords would match the identifier regex as well if we didn't catch them earlier, we can reuse the regex here

        // First check if we have a string

        auto stringToken = ProcessStringLiteral(source);
        if(stringToken.has_value()) {
            return {
                std::get<0>(stringToken.value()),
                true,
                std::get<1>(stringToken.value()),
                std::get<2>(stringToken.value())
            };
        }

        // If not, check for linebreaks before anything else
        auto lnToken = ProcessLineBreak(source);
        if(lnToken.has_value()) {
            return {
                    std::get<0>(lnToken.value()),
                    false,
                    std::get<1>(lnToken.value()),
                    std::get<2>(lnToken.value())
            };
        }

        // At last, check for number literal
        auto numberToken = ProcessNumberLiteral(source);
        if(numberToken.has_value()) {
            return {
                    std::get<0>(numberToken.value()),
                    false,
                    std::get<1>(numberToken.value()),
                    std::get<2>(numberToken.value())
            };
        }

        for(int offset = 0; offset < source.length(); offset++) {
            // Check for linebreaks, these could occur after removing comments, etc.
            lnToken = ProcessLineBreak(source);
            if(lnToken.has_value()) {
                return {
                        std::get<0>(lnToken.value()),
                        false,
                        std::get<1>(lnToken.value()),
                        std::get<2>(lnToken.value())
                };
            }
            // If we start with alphanumeric or underscore, we have a proper literal and not a symbol
            if (std::isalnum(source[offset]) || source[offset] == Symbols::SYMBOL_UNDERSCORE[0]) {
                if (_state == LexerState::SYMBOL) {
                    next = source.substr(0, offset);
                    Erase(source, offset);
                    auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                            next , false, _currentColumnStart, _currentColumnStart + offset + 1
                    };
                    _currentColumnStart = _currentColumnStart + offset + 1;

                    return result;
                }
                _state = LexerState::VALUE;
            }
            // We have some sort of whitespace
            else if (std::isspace(source[offset])) {
                // Edge case 1: If the line starts with a whitespace(not \n), remove it immediately
                if(offset == 0) {
                    auto lnToken = ProcessLineBreak(source);
                    if(lnToken.has_value()) {
                        auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                                "\n" , false, _currentColumnStart, _currentColumnStart
                        };
                        _currentColumnStart = 0;

                        return result;
                    } else {
                        Erase(source, offset + 1);
                        _currentColumnStart++;
                        return NextToken(source);
                    }
                }
                // If we hit a whitespace, we automatically end the Token if not in a string literal.
                next = source.substr(0, offset);
                // Edge case 2: If the character is a linebreak, we don't remove it from the source str as linebreaks are tokens
                Erase(source, offset + (source[offset] == '\n' ? 0 : 1));

                auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                        next , false, _currentColumnStart, _currentColumnStart + offset - 1
                };
                _currentColumnStart = _currentColumnStart + offset + 1;

                return result;
            }
                // We have symbol, now we need to check if it is a two or one chars symbol
            else {
                if (_state == LexerState::VALUE) {
                    next = source.substr(0, offset);
                    Erase(source, offset);
                    auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                            next , false, _currentColumnStart, _currentColumnStart + offset - 1
                    };
                    _currentColumnStart = _currentColumnStart + offset;

                    return result;
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
                    Erase(source, 2);
                    _currentColumnStart += 2;
                    _state = LexerState::NONE;

                    // Extra check: Remove all characters until comments are ended if a comment is detected
                    if(next == Symbols::SYMBOL_COMMENT) {
                        RemoveComment(source, false, _currentLine, _currentColumnEnd);
                        continue;
                    }

                    if(next == Symbols::SYMBOL_MULTILINE_COMMENT_BEGIN) {
                        RemoveComment(source, true, _currentLine, _currentColumnEnd);
                        continue;
                    }

                    return { next, false, 1, 2 };
                } else {
                    if(TryGetSpecial(source.substr(0, offset + 1)) != HTokenType::INVALID) {
                        next = source.substr(0, 1);
                        Erase(source, 1);
                        _state = LexerState::NONE;

                        auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                                next , false, _currentColumnStart, _currentColumnStart
                        };
                        _currentColumnStart = _currentColumnStart + 1;

                        return result;
                    }

                    if(TryGetOperator(source.substr(0, offset + 1)) != HTokenType::INVALID) {
                        next = source.substr(0, 1);
                        Erase(source, 1);
                        _state = LexerState::NONE;

                        auto result = std::tuple<std::string, bool, uint64_t, uint64_t> {
                                next , false, _currentColumnStart, _currentColumnStart
                        };
                        _currentColumnStart = _currentColumnStart + 1;

                        return result;
                    }
                }

                Erase(source, 1);
                _currentColumnStart = _currentColumnStart + 1;

                _state = LexerState::NONE;

                throw HLexerError("Undefined symbol");
            }
        }

        return { next , false, 1, 1 };
    }

    void PushToken(
            HTokenType type,
            HTokenFamily family,
            std::string_view value,
            std::string_view fileName,
            uint64_t line,
            uint64_t columnStart,
            uint64_t columnEnd,
            std::vector<HToken>& queue) {
        queue.push_back(HToken{
                .Family = family,
                .Type = type,
                .Value = std::string(value),
                .FileName = std::string(fileName),
                .Line = line,
                .ColumnStart = columnStart,
                .ColumnEnd = columnEnd
        });
    }

    HLexer::HLexer() = default;

    std::vector<HToken> HLexer::Tokenize(std::string stream, std::string& fileName) {
        std::vector<HToken> tokens = {};

        _currentLine = 1;
        _currentColumnEnd = 1;
        _state = LexerState::NONE;

        std::string content = std::move(stream);
        // Use the first two chars for context. Code must start with a keyword, which is 2 chars min
        std::tuple<std::string, bool, uint64_t, uint64_t> currentToken;

        _state = LexerState::NONE;

        auto currentType = HTokenType::INVALID;

        do {
            try {
                currentToken = NextToken(content);
            } catch(std::exception& error) {
                PushToken(
                        HTokenType::ERROR,
                        HTokenFamily::ERROR,
                        error.what(),
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                                tokens
                                );
                _state = LexerState::NONE;
                continue;
            }

            // If we are in string mode the next sequence is guaranteed to be a string
            if(std::get<1>(currentToken)) {
                _state = LexerState::NONE;
                PushToken(
                        HTokenType::STRING,
                        HTokenFamily::LITERAL,
                        std::get<0>(currentToken),
                                fileName,
                                _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                                tokens
                                );
                continue;
            }

            // Line break
            if(std::get<0>(currentToken)[0] == '\n') {
                PushToken(
                        HTokenType::LINEBREAK,
                        HTokenFamily::LINEBREAK,
                        std::get<0>(currentToken),
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
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
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
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
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
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
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
                );

                continue;
            }

            currentType = TryGetSpecial(std::get<0>(currentToken));

            if(currentType != HTokenType::INVALID) {
                // Edge case, if a string is detected, swap the lexer to string mode
                PushToken(
                        currentType,
                        HTokenFamily::SPECIAL,
                        std::get<0>(currentToken),
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
                );
                continue;
            }

            if(std::isdigit(std::get<0>(currentToken)[0])) {
                PushToken(
                        HTokenType::NUM,
                        HTokenFamily::LITERAL,
                        std::get<0>(currentToken),
                        fileName,
                        _currentLine,
                        std::get<2>(currentToken),
                        std::get<3>(currentToken),
                        tokens
                );
                continue;
            }

        } while(!content.empty());

        PushToken(
                HTokenType::END_OF_FILE,
                HTokenFamily::END_OF_FILE,
                "",
                fileName,
                _currentLine,
                std::get<2>(currentToken),
                std::get<3>(currentToken),
                tokens
        );

        return tokens;
    }
}