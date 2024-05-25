#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstInheritanceNode : HAstNode {
        std::vector<std::string_view> InheritedTypes;
    };
}