#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstProtocolNode : HAstTypeNode {
        std::string Name;
        std::shared_ptr<HAstInheritanceNode> Inheritance;

        HAstProtocolNode() {
            Name = "";
            Inheritance = nullptr;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Protocol;
        }

        HAstProtocolNode(std::string name, std::shared_ptr<HAstInheritanceNode> inheritance) : Name(name), Inheritance(inheritance) {
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Protocol;
        }
    };
}