#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstImportNode : HAstStatementNode {
        std::string Target;

        HAstImportNode() {
            StatementType = ExpressionType::Import;
        }
    };
}