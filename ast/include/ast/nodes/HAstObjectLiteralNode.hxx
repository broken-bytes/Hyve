#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstLiteralArgument {
        std::string Name;
        std::shared_ptr<HAstExpressionNode> Value;
    };

    struct HAstObjectLiteralNode : public HAstExpressionNode {
        std::shared_ptr<HAstNode> Object;
        std::vector<HAstLiteralArgument> Arguments;

        HAstObjectLiteralNode() {
            Name = "";
            ExpressionType = ExpressionType::ObjectLiteral;
        }
    };
}