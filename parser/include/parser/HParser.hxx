#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HClassParser.hxx"
#include "parser/parsers/HModuleParser.hxx"
#include <lexer/HToken.hxx>
#include <lexer/HTokenStream.hxx>
#include <lexer/HTokenType.hxx>
#include <core/HAccessLevel.hxx>
#include <core/HErrorHandler.hxx>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

namespace Hyve::AST {
	struct HAstNode;
	struct HAstImportNode;
}

namespace Hyve::Parser {
    class HParser : public IHParser {
        public:
        HParser(
            const std::shared_ptr<Core::HErrorHandler>& errorHandler,
            const std::shared_ptr<HModuleParser> moduleParser
        );
        ~HParser() final = default;

        std::shared_ptr<AST::HAstNode> Parse(Lexer::HTokenStream& stream) override;

        private:
            std::shared_ptr<Core::HErrorHandler> _errorHandler;
            // Different parsers for each context
            std::shared_ptr<HModuleParser> _moduleParser;
            std::shared_ptr<AST::HAstImportNode> ParseImport(Lexer::HTokenStream& stream) const;
    };
}
