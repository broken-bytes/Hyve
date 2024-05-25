#include "parser/HAstNode.hxx"
#include "parser/Nodes/HAstTypeNode.hxx"
#include <memory>
#include <string>

namespace Hyve::Parser {
    struct HAstArrayNode : public HAstTypeNode {
        std::shared_ptr<HAstTypeNode> Type;
    };
}