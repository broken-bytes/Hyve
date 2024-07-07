#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstWithAccessLevelNode.hxx"
#include "ast/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstInitDeclNode : public HAstWithAccessLevelNode {
        std::vector<HAstParamater> Parameters;

        HAstInitDeclNode() {
            Type = HAstNodeType::Init;
            Parameters = std::vector<HAstParamater>();
        }
    };
}