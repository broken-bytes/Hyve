#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstInitDeclNode : HAstNode {
        std::vector<HAstParamater> Parameters;

        HAstInitDeclNode() {
            Type = HAstNodeType::Func;
            Parameters = std::vector<HAstParamater>();
        }
    };
}