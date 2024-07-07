#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include "ast/HAstNodeType.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstIdentifierNode : HAstExpressionNode {
        HAstIdentifierNode() {
            ExpressionType = ExpressionType::Identifier;
        }
    };
}