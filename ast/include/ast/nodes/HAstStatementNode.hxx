#pragma once

#include "ast/HAstNode.hxx"
#include <string>

namespace Hyve::AST {
    enum class StatementType {
        Import,
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
        StatementType StatementType;
    };
}