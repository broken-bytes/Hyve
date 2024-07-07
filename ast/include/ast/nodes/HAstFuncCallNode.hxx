#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstCallParamater {
        std::string Name;
        std::shared_ptr<HAstExpressionNode> Value;
    };

    struct HAstFuncCallNode : HAstExpressionNode {
        std::shared_ptr<HAstNode> Target;
        std::vector<HAstCallParamater> Parameters;

        HAstFuncCallNode() {
            ExpressionType = ExpressionType::FunctionCall;
        }
    };
}