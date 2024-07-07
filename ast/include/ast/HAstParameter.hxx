#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <memory>

namespace Hyve::AST {
    struct HAstParamater {
        std::string Name;
        std::shared_ptr<HAstTypeNode> Type;
    };
}