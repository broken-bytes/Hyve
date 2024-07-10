#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstCallArgument {
        std::string Name;
        std::shared_ptr<HAstExpressionNode> Value;
    };

    struct HAstFuncCallNode : HAstExpressionNode {
        std::shared_ptr<HAstNode> Target;
        std::vector<HAstCallArgument> Arguments;

        HAstFuncCallNode() {
            ExpressionType = ExpressionType::FunctionCall;
        }
    };
}