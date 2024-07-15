#pragma once

namespace Hyve::AST {
    enum class HAstNodeType {
        Allocation,
        Assignment,
        Deallocation,
        Expression,
        Statement,
        NominalType,
        Import,
        Init,
        Func,
        PropertyDecl,
        VariableDecl,
        Literal,
        Identifier,
        Operator,
        IfStatement,
        ElseStatement,
        ForLoop,
        WhileLoop,
        BreakStatement,
        ContinueStatement,
        ReturnStatement,
        TryBlock,
        CatchBlock,
        File,
        Module,
        Namespace,
        Annotation,
        Program,
        CodeBlock,
    };

    enum class HAstTypeKind {
        Contract,
        Enum,
        File,
        Module,
        Struct,
        Function,
        Variable,
        UnknownKind,
    };
}