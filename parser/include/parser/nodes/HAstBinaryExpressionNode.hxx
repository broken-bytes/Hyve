#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/HAstOperatorType.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstBinaryOperator {
        HAstOperatorType Type;
    };

    struct HAstBinaryExpressionNode : HAstExpressionNode {
        std::shared_ptr<HAstExpressionNode> LHS;
        HAstBinaryOperator Operator;
        std::shared_ptr<HAstExpressionNode> RHS;
    };
}