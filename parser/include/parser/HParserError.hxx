#pragma once

#include <stdexcept>

namespace Hyve::Parser {
    class HParserError : public std::runtime_error {
    public:
        explicit HParserError(const std::string& message) : std::runtime_error(message) { }
        explicit HParserError(const char* message) : std::runtime_error(message) { }
    };
}