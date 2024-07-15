#pragma once

#include "ast/HAstNode.hxx"
#include "ast/HAstLiteralType.hxx"
#include "ast/nodes/HAstExpressionNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstLiteralNode : HAstExpressionNode {
        HAstLiteralType LiteralType;
        std::string Value;
    };
}