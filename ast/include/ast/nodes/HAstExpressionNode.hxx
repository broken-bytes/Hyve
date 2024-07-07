#pragma once

#include "ast/HAstNode.hxx"
#include "ast/nodes/HAstTypeNode.hxx"
#include <string>
#include <vector>

namespace Hyve::AST {
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