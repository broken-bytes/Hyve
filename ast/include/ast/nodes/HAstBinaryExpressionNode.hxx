#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include "ast/HAstOperatorType.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstBinaryExpressionNode : HAstExpressionNode {
        std::shared_ptr<HAstExpressionNode> LHS;
        HAstOperatorType Operator = HAstOperatorType::NOOP;
        std::shared_ptr<HAstExpressionNode> RHS;

        HAstBinaryExpressionNode() {
            ExpressionType = ExpressionType::BinaryOperation;
        }
    };
}