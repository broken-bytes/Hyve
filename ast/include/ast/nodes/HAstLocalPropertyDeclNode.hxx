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
        bool IsMutable = false;
        std::shared_ptr<HAstTypeNode> TypeNode = nullptr;
        std::shared_ptr<HAstExpressionNode> Initializer = nullptr;

        HAstLocalPropertyDeclNode() {
            Name = "";
            Type = HAstNodeType::PropertyDecl;
        }
    };
}