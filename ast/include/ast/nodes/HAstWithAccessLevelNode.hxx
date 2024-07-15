#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstStatementNode.hxx"
#include <core/HAccessLevel.hxx>

namespace Hyve::AST {
    struct HAstWithAccessLevelNode : public HAstStatementNode {
        Core::HAccessLevel AccessLevel = Core::HAccessLevel::Internal;
        bool IsStatic = false;

        HAstWithAccessLevelNode() = default;
    };
}