#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstVarDeclNode : HAstNode {
        std::string Name;
        bool IsMutable;
        std::shared_ptr<HAstTypeNode> Type;
        std::shared_ptr<HAstExpressionNode> Initializer;
    };
}