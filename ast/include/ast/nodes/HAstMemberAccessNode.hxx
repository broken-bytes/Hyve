#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>

namespace Hyve::AST {
    struct HAstMemberAccessNode : HAstExpressionNode {
        std::shared_ptr<HAstExpressionNode> Target;
        std::shared_ptr<HAstExpressionNode> Member;
    };
}