#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include <core/HAccessLevel.hxx>

namespace Hyve::AST {
    struct HAstWithAccessLevelNode : public HAstStatementNode {
        Core::HAccessLevel AccessLevel;
        bool IsStatic = false;

        HAstWithAccessLevelNode() = default;
    };
}