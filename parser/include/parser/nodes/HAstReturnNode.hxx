#pragma once

#include "parser/HAstNode.hxx"
#include "parser/Nodes/HAstStatementNode.hxx"
#include "parser/Nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstReturnNode : HAstStatementNode {

        HAstReturnNode() {
            Type = StatementType::Return;
        }
    };
}