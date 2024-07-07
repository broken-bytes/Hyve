#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include "ast/nodes/HAstInheritanceNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstStructNode : HAstTypeNode {
        std::shared_ptr<HAstInheritanceNode> Inheritance;

        HAstStructNode() {
            Name = "";
            Inheritance = nullptr;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Struct;
        }

        HAstStructNode(std::string name, std::shared_ptr<HAstInheritanceNode> inheritance) : Inheritance(inheritance) {
            Name = name;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Struct;
        }
    };
}