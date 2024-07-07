#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstInheritanceNode : HAstNode {
        std::vector<std::string_view> InheritedTypes;
    };
}