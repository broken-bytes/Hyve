#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstWithAccessLevelNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstLocalPropertyDeclNode : public HAstNode {
        std::string Name;
        bool IsMutable;
        std::shared_ptr<HAstTypeNode> TypeNode;
        std::shared_ptr<HAstExpressionNode> Initializer;

        HAstLocalPropertyDeclNode() {
            Name = "";
            IsMutable = false;
            Initializer = nullptr;
            Type = HAstNodeType::Decl;
            TypeNode = nullptr;
        }
    };
}