#pragma once

#include "parser/HAstNode.hxx"
#include "parser/Nodes/HAstExpressionNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstMemberAccessNode : HAstExpressionNode {
        std::string Target;
        std::shared_ptr<HAstNode> Call;
    };
}