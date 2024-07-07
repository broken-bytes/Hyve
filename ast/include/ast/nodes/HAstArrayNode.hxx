#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <memory>
#include <string>

namespace Hyve::AST {
    struct HAstArrayNode : public HAstTypeNode {
        std::shared_ptr<HAstTypeNode> Type;
    };
}