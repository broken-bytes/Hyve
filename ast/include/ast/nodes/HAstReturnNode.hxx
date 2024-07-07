#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstReturnNode : HAstStatementNode {

        HAstReturnNode() {
            StatementType = StatementType::Return;
        }
    };
}