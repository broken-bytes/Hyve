#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
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