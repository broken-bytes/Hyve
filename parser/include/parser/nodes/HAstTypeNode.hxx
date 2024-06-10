#pragma once

#include "parser/HAstNode.hxx"
#include <core/HAccessLevel.hxx>
#include <string>

namespace Hyve::Parser {
    struct HAstTypeNode : HAstNode {
        HAstTypeKind Kind;

        HAstTypeNode() {
            Kind = HAstTypeKind::UnknownKind;
        }

        virtual ~HAstTypeNode() = default;
    };
}