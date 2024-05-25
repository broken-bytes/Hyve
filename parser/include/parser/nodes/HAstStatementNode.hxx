#pragma once

#include "parser/HAstNode.hxx"
#include <string>

namespace Hyve::Parser {
    enum class StatementType {
        VariableDeclaration,
        VariableAssignment,
        Return,
        If,
        While,
        For,
        Break,
        Continue,
    };

    struct HAstStatementNode : HAstNode {
        StatementType Type;
    };
}