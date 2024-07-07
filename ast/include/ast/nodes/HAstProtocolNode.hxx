#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
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