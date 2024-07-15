#pragma once

#include "ast/HAstNode.hxx"
#include "ast/HAstOperatorType.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstUnaryExpressionNode : HAstExpressionNode {
        HAstOperatorType Operator;
        std::shared_ptr<HAstExpressionNode> Operand;
    };
}