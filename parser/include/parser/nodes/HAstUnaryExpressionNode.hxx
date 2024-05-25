#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include "parser/HAstOperatorType.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::Parser {

    struct HAstUnaryOperator {
        HAstOperatorType Type;
    };

    struct HAstUnaryExpressionNode : HAstExpressionNode {
        HAstUnaryOperator Operator;
        std::shared_ptr<HAstExpressionNode> Operand;
    };
}