#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstWithAccessLevelNode.hxx"
#include "ast/HAstParameter.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstFuncDeclNode : public HAstWithAccessLevelNode {
        bool InferReturnType;
        std::shared_ptr<HAstTypeNode> ReturnType;
        std::vector<HAstParamater> Parameters;

        HAstFuncDeclNode() {
            Type = HAstNodeType::Func;
            InferReturnType = true;
            ReturnType = nullptr;
            Parameters = std::vector<HAstParamater>();
        }
    };
}