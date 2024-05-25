#pragma once

#include "HAstNodeType.hxx"

#include <memory>
#include <vector>

namespace Hyve::Parser {
    struct HAstNode {
        virtual ~HAstNode() = default;
        HAstNodeType Type;
        std::vector<std::shared_ptr<HAstNode>> Children;
    };
}