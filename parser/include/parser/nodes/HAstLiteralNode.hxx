#pragma once

#include "parser/HAstNode.hxx"
#include "parser/Nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstLiteralNode : HAstExpressionNode {
        std::string Type;
        std::string Value;
    };
}