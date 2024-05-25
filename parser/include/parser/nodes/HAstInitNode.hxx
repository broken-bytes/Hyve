#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/HAstParameter.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstInitNode : HAstNode {
        std::vector<HAstParamater> Parameters;
    };
}