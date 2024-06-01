#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"
#include <core/HAccessLevel.hxx>

namespace Hyve::Parser {
    struct HAstWithAccessLevelNode : public HAstStatementNode {
        Core::HAccessLevel AccessLevel;

        HAstWithAccessLevelNode() = default;
    };
}