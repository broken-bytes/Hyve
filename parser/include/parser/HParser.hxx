#pragma once

#include "parser/IHParser.hxx"
#include "parser/parsers/HClassParser.hxx"
#include "parser/parsers/HModuleParser.hxx"
#include "parser/nodes/HAstImportNode.hxx"
#include <lexer/HToken.hxx>
#include <lexer/HTokenType.hxx>
#include <core/HAccessLevel.hxx>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

namespace Hyve::Parser {
    class HParser : public IHParser {
        public:
        HParser() = default;
        ~HParser() final = default;

        std::shared_ptr<HAstNode> Parse(std::string_view fileName, std::vector<Lexer::HToken>& tokens) override;

        private:
            // Different parsers for each context
            std::shared_ptr<HModuleParser> _moduleParser;
            std::shared_ptr<HClassParser> _classParser;

            std::shared_ptr<HAstImportNode> ParseImport();
    };

    std::unique_ptr<HParser> Create();
}
