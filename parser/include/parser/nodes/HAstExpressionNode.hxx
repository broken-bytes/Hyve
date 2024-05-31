#pragma once

#include "parser/HAstNode.hxx"
#include "parser/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::Parser {
    enum class ExpressionType {
        Literal,
        Identifier,
        FunctionCall,
        BinaryOperation,
        UnaryOperation,
        TypeCast,
        TypeOf,
        SizeOf,
        ArrayAccess,
        MemberAccess,
        PointerAccess,
        PointerDereference,
        AddressOf,
        New,
        Delete,
        Lambda,
        Tuple,
        Array,
        Struct,
        Union,
        Enum,
        If,
        While,
        For,
        Switch,
        Return,
        Break,
        Continue,
        Label,
        Block,
        Parentheses,
        Error
    };

    struct HAstExpressionNode : HAstNode {
        ~HAstExpressionNode() override = default;
        ExpressionType ExpressionType;
        std::shared_ptr<HAstTypeNode> ReturnType;
    };
}