#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstStructNode : HAstNode {
        std::string Name;
        std::shared_ptr<HAstInheritanceNode> Inheritance;
    };
}