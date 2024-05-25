#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstFuncDeclNode : HAstNode {
        std::string Name;
        bool InferReturnType;
        std::string ReturnType;
        std::vector<HAstParamater> Parameters;
    };
}