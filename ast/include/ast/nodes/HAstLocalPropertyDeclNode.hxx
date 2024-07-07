#pragma once

#include "ast/HAstNode.hxx"
#include "ast/HAstNodeType.hxx"
#include "ast/nodes/HAstWithAccessLevelNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include <memory>
#include <string>

namespace Hyve::AST {
    struct HAstLocalPropertyDeclNode : public HAstNode {
        std::string Name;
        bool IsMutable;
        std::shared_ptr<HAstTypeNode> TypeNode;
        std::shared_ptr<HAstExpressionNode> Initializer;

        HAstLocalPropertyDeclNode() {
            Name = "";
            IsMutable = false;
            Initializer = nullptr;
            Type = HAstNodeType::PropertyDecl;
            TypeNode = nullptr;
        }
    };
}