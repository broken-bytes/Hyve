#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstImportNode : HAstStatementNode {
        HAstImportNode() {
            StatementType = StatementType::Import;
        }
    };
}