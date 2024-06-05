#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstWithAccessLevelNode.hxx"
#include "parser/HAstParameter.hxx"
#include <memory>
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstFuncDeclNode : public HAstWithAccessLevelNode {
        std::string Name;
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