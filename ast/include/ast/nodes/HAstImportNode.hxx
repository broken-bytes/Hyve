#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstImportNode : HAstStatementNode {
        HAstImportNode() {
            Type = HAstNodeType::Import;
            StatementType = StatementType::Import;
        }
    };
}