#pragma once

#include "parser/HAstNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstModuleDeclNode : public HAstNode {
        HAstModuleDeclNode() {
            Name = "";
            Type = HAstNodeType::Module;
        }

        std::string Name;
    };
}