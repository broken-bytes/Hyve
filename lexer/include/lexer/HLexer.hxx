#pragma once

#include "lexer/HToken.hxx"
#include "lexer/HTokenStream.hxx"
#include "lexer/processors/HControlFlowProcessor.hxx"
#include "lexer/processors/HGroupingProcessor.hxx"
#include "lexer/processors/HIdentifierProcessor.hxx"
#include "lexer/processors/HKeywordProcessor.hxx"
#include "lexer/processors/HLiteralProcessor.hxx"
#include "lexer/processors/HNumberProcessor.hxx"
#include "lexer/processors/HOperatorProcessor.hxx"
#include "lexer/processors/HPunctuationProcessor.hxx"
#include "lexer/processors/HSpecialProcessor.hxx"

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
        explicit HLexer(
            std::shared_ptr<HControlFlowProcessor> controlFlowProcessor,
            std::shared_ptr<HGroupingProcessor> groupingProcessor,
            std::shared_ptr<HIdentifierProcessor> identifierProcessor,
            std::shared_ptr<HKeywordProcessor> keywordProcessor,
            std::shared_ptr<HLiteralProcessor> literalProcessor,
            std::shared_ptr<HOperatorProcessor> operatorProcessor,
            std::shared_ptr<HPunctuationProcessor> punctuationProcessor,
            std::shared_ptr<HSpecialProcessor> specialProcessor
        );
        [[nodiscard]] HTokenStream Tokenize(std::string stream, const std::string& fileName) const;

        static std::shared_ptr<HLexer> Create() {
            return std::make_shared<HLexer>(
				std::make_shared<HControlFlowProcessor>(),
				std::make_shared<HGroupingProcessor>(),
				std::make_shared<HIdentifierProcessor>(),
				std::make_shared<HKeywordProcessor>(),
				std::make_shared<HLiteralProcessor>(std::make_shared<HNumberProcessor>()),
				std::make_shared<HOperatorProcessor>(),
				std::make_shared<HPunctuationProcessor>(),
				std::make_shared<HSpecialProcessor>()
			);
        }
    private:
        bool NextIsWhitespace(std::string_view source) const;
        bool NextIsLineBreak(std::string_view source) const;
        void RemoveComment(
            std::string& source, 
            bool multiLine, 
            uint64_t& currentLine, 
            uint64_t& currentColumn
        ) const;

        void ProcessNextSequence(
            std::string_view source,
            std::string_view file, 
            uint64_t currentLine, 
            uint64_t& currentColumn,
            std::vector<HToken>& tokens
        ) const;

        HToken ProcessNextToken(std::string_view source) const;

        std::shared_ptr<HControlFlowProcessor> _controlFlowProcessor;
        std::shared_ptr<HGroupingProcessor> _groupingProcessor;
        std::shared_ptr<HIdentifierProcessor> _identifierProcessor;
        std::shared_ptr<HKeywordProcessor> _keywordProcessor;
        std::shared_ptr<HLiteralProcessor> _literalProcessor;
        std::shared_ptr<HOperatorProcessor> _operatorProcessor;
        std::shared_ptr<HPunctuationProcessor> _punctuationProcessor;
        std::shared_ptr<HSpecialProcessor> _specialProcessor;
    };
}