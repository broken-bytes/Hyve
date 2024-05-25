#pragma once

#include <memory>
#include <vector>

namespace Hyve::Parser {
    struct HAstNode {
        virtual ~HAstNode() = default;
        std::vector<std::shared_ptr<HAstNode>> Children;
    };
}