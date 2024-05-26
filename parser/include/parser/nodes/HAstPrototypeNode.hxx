#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstPrototypeNode : HAstTypeNode {
        std::string Name;
        std::shared_ptr<HAstInheritanceNode> Inheritance;

        HAstPrototypeNode() {
            Name = "";
            Inheritance = nullptr;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Prototype;
        }

        HAstPrototypeNode(std::string name, std::shared_ptr<HAstInheritanceNode> inheritance) : Name(name), Inheritance(inheritance) {
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Prototype;
        }
    };
}