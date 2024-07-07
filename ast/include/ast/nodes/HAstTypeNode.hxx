#pragma once

#include "ast/HAstNode.hxx"
#include <core/HAccessLevel.hxx>
#include <string>

namespace Hyve::AST {
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