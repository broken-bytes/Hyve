#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstFuncDeclNode.hxx"
#include "parser/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstInitDeclNode : public HAstFuncDeclNode {
        HAstInitDeclNode() {
            Name = "init";
            Type = HAstNodeType::Func;
            Parameters = std::vector<HAstParamater>();
        }
    };
}