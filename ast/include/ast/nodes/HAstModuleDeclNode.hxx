#pragma once

#include "ast/HAstNode.hxx"
#include <string>

namespace Hyve::AST {
    struct HAstModuleDeclNode : public HAstNode {
        
        HAstModuleDeclNode() {
            Name = "";
            Type = HAstNodeType::Module;
        }
    };
}