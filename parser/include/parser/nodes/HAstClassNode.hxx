#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstInheritanceNode.hxx"

#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstClassNode : HAstTypeNode {
        std::shared_ptr<HAstInheritanceNode> Inheritance;

        HAstClassNode() {
            Name = "";
            Inheritance = nullptr;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Class;
        }

        HAstClassNode(
            std::string name, 
            std::shared_ptr<HAstInheritanceNode> inheritance
        ) : Inheritance(std::move(inheritance)) {
            Name = name;
            Type = HAstNodeType::NominalType;
            Kind = HAstTypeKind::Class;
        }
    };
}