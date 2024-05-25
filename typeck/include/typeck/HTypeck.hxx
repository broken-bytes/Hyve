#pragma once

#include <parser/HAstNode.hxx>

#include <string>
#include <vector>

namespace Hyve::Typeck {
    class HTypeck {
    public:
        HTypeck();
        [[nodiscard]] std::vector<std::string> BuildTypeTable(const Hyve::Parser::HAstNode& code);

    private:
    };
}