#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstCallParamater {
        std::string Name;
        std::shared_ptr<HAstNode> Value;
    };

    struct HAstFuncCallNode : HAstExpressionNode {
        std::string Name;
        std::vector<HAstCallParamater> Parameters;

        HAstFuncCallNode() {
            ExpressionType = ExpressionType::FunctionCall;
        }
    };
}