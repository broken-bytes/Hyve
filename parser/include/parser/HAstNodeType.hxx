#pragma once

namespace Hyve::Parser {
    enum class HAstNodeType {
        Assignment,
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
        Class,
        Enum,
        File,
        Module,
        Protocol,
        Prototype,
        Struct,
        Function,
        Variable,
        UnknownKind,
    };
}