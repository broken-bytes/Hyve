#pragma once

namespace Hyve::Parser {
    enum class HAstNodeType {
        Expression,
        Statement,
        NominalType,
        Func,
        Decl,
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
        Protocol,
        Prototype,
        Struct,
        Function,
    };
}