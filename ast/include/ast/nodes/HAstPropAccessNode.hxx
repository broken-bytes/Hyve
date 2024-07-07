#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstPropAccessNode : HAstExpressionNode {
        std::shared_ptr<HAstNode> Target;
    };
}
