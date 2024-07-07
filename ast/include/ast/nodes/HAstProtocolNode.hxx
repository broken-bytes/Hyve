#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
    struct HAstProtocolNode : HAstTypeNode {
        std::shared_ptr<HAstInheritanceNode> Inheritance;

        HAstProtocolNode() {
            Name = "";
            Inheritance = nullptr;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Protocol;
        }

        HAstProtocolNode(std::string name, std::shared_ptr<HAstInheritanceNode> inheritance) : Inheritance(inheritance) {
            Name = name;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Protocol;
        }
    };
}