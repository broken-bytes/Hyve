#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <memory>

namespace Hyve::Parser {
    struct HAstParamater {
        std::string Name;
        std::shared_ptr<HAstTypeNode> Type;
    };
}