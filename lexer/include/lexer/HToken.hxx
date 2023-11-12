#pragma once

#include "lexer/HTokenType.hxx"
#include <string>

namespace Hyve::Lexer {
    struct HToken {
        HTokenFamily Family;
        HTokenType Type;
        std::string Value;
        std::string FileName;
        uint64_t Line;
        uint64_t Column;
    };
}