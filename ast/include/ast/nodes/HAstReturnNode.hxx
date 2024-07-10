#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstReturnNode : HAstStatementNode {
        std::shared_ptr<HAstExpressionNode> Value;

        HAstReturnNode() {
            StatementType = StatementType::Return;
        }
    };
}