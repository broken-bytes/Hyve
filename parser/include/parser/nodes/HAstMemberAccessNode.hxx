#pragma once

#include "parser/HAstNode.hxx"
#include "parser/Nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstMemberAccessNode : HAstExpressionNode {
        std::shared_ptr<HAstExpressionNode> Target;
        std::shared_ptr<HAstExpressionNode> Member;
    };
}