#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstFuncDeclNode.hxx"
#include "ast/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstInitDeclNode : public HAstFuncDeclNode {
        HAstInitDeclNode() {
            Name = "init";
            Type = HAstNodeType::Func;
            Parameters = std::vector<HAstParamater>();
        }
    };
}