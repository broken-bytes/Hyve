#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include "parser/nodes/HAstExpressionNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    struct HAstPropAccessNode : HAstExpressionNode {
        std::shared_ptr<HAstNode> Target;
    };
}
