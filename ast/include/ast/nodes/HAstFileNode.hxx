#pragma once

#include "ast/HAstNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstFileNode : public HAstNode {
        HAstFileNode() {
            Name = "";
            Type = HAstNodeType::File;
        }
    };
}