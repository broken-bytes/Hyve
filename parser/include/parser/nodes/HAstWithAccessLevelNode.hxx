#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstStatementNode.hxx"

namespace Hyve::Parser {
    struct HAstWithAccessLevelNode : public HAstStatementNode {

        HAstWithAccessLevelNode() {

        }
    };
}