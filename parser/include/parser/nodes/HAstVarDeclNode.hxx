#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstWithAccessLevelNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstVarDeclNode : public HAstWithAccessLevelNode {
        std::string Name;
        bool IsMutable;
        std::shared_ptr<HAstTypeNode> TypeNode;
        std::shared_ptr<HAstExpressionNode> Initializer;

        HAstVarDeclNode() {
            Name = "";
            IsMutable = false;
            Initializer = nullptr;
            Type = HAstNodeType::Decl;
            TypeNode = nullptr;
        }
    };
}