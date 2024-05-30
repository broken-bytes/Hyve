#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
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