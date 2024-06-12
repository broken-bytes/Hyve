#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstWithAccessLevelNode.hxx"
#include "parser/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstInitDeclNode : public HAstWithAccessLevelNode {
        std::vector<HAstParamater> Parameters;

        HAstInitDeclNode() {
            Type = HAstNodeType::Init;
            Parameters = std::vector<HAstParamater>();
        }
    };
}