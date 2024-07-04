#pragma once

#include "parser/HAstNode.hxx"
#include <core/HAccessLevel.hxx>
#include <string>

namespace Hyve::Parser {
    struct HAstTypeNode : HAstNode {
        HAstTypeKind Kind;
        std::string Module;
        std::weak_ptr<HAstTypeNode> ParentType;
        std::vector<std::shared_ptr<HAstTypeNode>> ChildTypes;

        HAstTypeNode() {
            Kind = HAstTypeKind::UnknownKind;
        }

        virtual ~HAstTypeNode() = default;
    };
}