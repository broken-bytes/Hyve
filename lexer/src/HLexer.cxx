#include "lexer/HLexer.hxx"
#include "lexer/HLexerError.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenKeywords.hxx"
#include "lexer/HTokenSymbols.hxx"
#include "lexer/HTokenType.hxx"
#include <core/HCompilerError.hxx>
#include <cstring>
#include <exception>
#include <optional>
#include <ranges>
#include <regex>
#include <stdexcept>
#include <string_view>

namespace Hyve::Lexer {
    void Erase(std::string& source, size_t count) {
        source.erase(0, count);
    }

    HLexer::HLexer(
        std::shared_ptr<HControlFlowProcessor> controlFlowProcessor,
        std::shared_ptr<HGroupingProcessor> groupingProcessor,
        std::shared_ptr<HIdentifierProcessor> identifierProcessor,
        std::shared_ptr<HKeywordProcessor> keywordProcessor,
        std::shared_ptr<HLiteralProcessor> literalProcessor,
        std::shared_ptr<HOperatorProcessor> operatorProcessor,
        std::shared_ptr<HPunctuationProcessor> punctuationProcessor,
        std::shared_ptr<HSpecialProcessor> specialProcessor
    ) : _controlFlowProcessor(controlFlowProcessor),
		_groupingProcessor(groupingProcessor),
		_identifierProcessor(identifierProcessor),
		_keywordProcessor(keywordProcessor),
		_literalProcessor(literalProcessor),
		_operatorProcessor(operatorProcessor),
		_punctuationProcessor(punctuationProcessor),
		_specialProcessor(specialProcessor) {}

    void HLexer::RemoveComment(
        std::string& source,
        bool multiLine,
        uint64_t& currentLine,  // Pass by reference to update the line
        uint64_t& currentColumn // Pass by reference to update the column
    ) const {
        if (multiLine) {
            auto endPos = source.find(Symbols::SYMBOL_MULTILINE_COMMENT_END);
            if (endPos == std::string::npos) {
                // Handle the case where the comment is not closed
                return;
            }

            // Count the number of newlines within the comment
            for (size_t i = 0; i < endPos; ++i) {
                if (source[i] == '\n') {
                    currentLine++;
                    currentColumn = 0; // Reset column at the start of a new line
                }
                else if (source[i] == '\r') {
                    // Handle carriage returns if present in your source
                }
            }

            source.erase(0, endPos + 2);  // Erase up to and including the delimiter
        }
        else {
            auto endPos = source.find_first_of("\r\n"); // Find the first line break
            if (endPos != std::string::npos) {
                currentLine++;
                currentColumn = 0; // Reset column at the start of a new line
            }

            source.erase(0, endPos);  // Erase up to the line break
        }
    }

    bool HLexer::NextIsWhitespace(std::string_view source) const {
        return std::isspace(source.back());
    }
     
    bool HLexer::NextIsLineBreak(std::string_view source) const{
        if (source.ends_with('\n')) {
            return true;
        }

        return false;
    }

    void HLexer::ProcessNextSequence(
        std::string_view source,
        std::string_view file,
        uint64_t currentLine,
        uint64_t& currentColumn,
        std::vector<HToken>& tokens
    ) const {
        auto currentToken = std::string(source);

        while (!currentToken.empty()) {
            auto token = ProcessNextToken(std::string_view(currentToken));
            UPDATE_TOKEN(token, file, currentLine, currentColumn);

            // Append the token to the list of tokens
            tokens.push_back(token);

            // Erase the token's length from the source
            Erase(currentToken, token.Value.size());

            // Update the current column
            currentColumn += token.Value.size();
        }
    }

    HToken HLexer::ProcessNextToken(
        std::string_view source
    ) const {
        if (auto control = _controlFlowProcessor->Process(source); control.has_value()) {
            return control.value();
        }

        if (auto grouping = _groupingProcessor->Process(source); grouping.has_value()) {
			return grouping.value();
		}

        if (auto keyword = _keywordProcessor->Process(source); keyword.has_value()) {
			return keyword.value();
        }

        if (auto lit = _literalProcessor->Process(source); lit.has_value()) {
            return lit.value();
        }

        if (auto op = _operatorProcessor->Process(source); op.has_value()) {
            return op.value();
        }

        if (auto punctuation = _punctuationProcessor->Process(source); punctuation.has_value()) {
			return punctuation.value();
		}

        if (auto identifier = _identifierProcessor->Process(source); identifier.has_value()) {
            return identifier.value();
        }

        if (auto special = _specialProcessor->Process(source); special.has_value()) {
			return special.value();
		}

        return MAKE_TOKEN(HTokenType::ERROR, std::string(source));
    }

    HTokenStream HLexer::Tokenize(const std::string& stream, std::string_view fileName) const {
        using enum HTokenType;
        using namespace Symbols;
        std::vector<HToken> tokens = {};

        uint64_t currentLine = 1;
        uint64_t currentColumnStart = 1;

        // Normalize the source to UNIX line endings
        auto normalizedStream = std::regex_replace(stream, std::regex("\r\n"), "\n");

        // We go over each character in the source code
        // Some rules are:
        // 1. If we encounter a comment, we remove it
        // 2. If we encounter a whitespace, we skip it
        // 3. If we encounter a line break, we increment the line number and reset the column number
        //    Additionally, we parse the line break as a token
        // 4. The different processors are responsible for parsing the different types of tokens

        auto currentToken = (normalizedStream | std::views::split(' ')).front();

        while (!normalizedStream.empty()) {
            // Check if the next token is a comment
            if (normalizedStream.starts_with(SYMBOL_COMMENT)) {
				Erase(normalizedStream, std::strlen(SYMBOL_COMMENT));
				RemoveComment(normalizedStream, false, currentLine, currentColumnStart);
			} 
			else if (normalizedStream.starts_with(SYMBOL_MULTILINE_COMMENT_BEGIN)) {
				Erase(normalizedStream, std::strlen(SYMBOL_MULTILINE_COMMENT_BEGIN));
				RemoveComment(normalizedStream, true, currentLine, currentColumnStart);
			}
			else {
				ProcessNextSequence(
                    std::string_view(currentToken),
                    fileName, 
                    currentLine, 
                    currentColumnStart, 
                    tokens
                );
                Erase(normalizedStream, currentToken.size());

                // Also erase the whitespace if normalizedStream is not empty
                if (!normalizedStream.empty()) {
					Erase(normalizedStream, 1);
				}
			}

            if(!normalizedStream.empty()) {
                currentToken = (normalizedStream | std::views::split(' ')).front();
			}
        }

        // Add the end of file token
        tokens.push_back(MAKE_TOKEN(END_OF_FILE, "EOF"));

        return HTokenStream(tokens);
    }
}