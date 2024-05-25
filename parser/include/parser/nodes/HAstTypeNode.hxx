#pragma once

#include "parser/HAstNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstTypeNode : HAstNode {
        std::string Value;

        virtual ~HAstTypeNode() = default;
    };
}