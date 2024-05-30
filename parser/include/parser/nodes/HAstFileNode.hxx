#pragma once

#include "parser/HAstNode.hxx"
#include <string>

namespace Hyve::Parser {
    struct HAstFileNode : public HAstNode {
        HAstFileNode() {
            Name = "";
            Type = HAstNodeType::File;
        }

        std::string Name;
    };
}