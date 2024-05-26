#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstTypeNode : HAstNode {
        std::string Name;
        HAstTypeKind Kind;

        virtual ~HAstTypeNode() = default;
    };
}