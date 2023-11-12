#pragma once

#include <lexer/HToken.hxx>
#include <vector>

namespace Hyve::Parser {
    class HParser {
        public:
        HParser(); 
        void Parse(std::vector<Lexer::HToken> tokens) const;
    };
}