SET(
    HEADERS
    include/ast/HAst.hxx
    include/ast/HAstNode.hxx
    include/ast/HAstNodeType.hxx
    include/ast/HAstLiteralType.hxx
    include/ast/HAstOperatorType.hxx
    include/ast/HAstParameter.hxx
    include/ast/nodes/HAstArrayNode.hxx
    include/ast/nodes/HAstAssignmentNode.hxx
    include/ast/nodes/HAstBinaryExpressionNode.hxx
    include/ast/nodes/HAstBlockNode.hxx
    include/ast/nodes/HAstExpressionNode.hxx
    include/ast/nodes/HAstFileNode.hxx
    include/ast/nodes/HAstFuncCallNode.hxx
    include/ast/nodes/HAstFuncDeclNode.hxx
    include/ast/nodes/HAstIdentifierNode.hxx
    include/ast/nodes/HAstImportNode.hxx
    include/ast/nodes/HAstInheritanceNode.hxx
    include/ast/nodes/HAstInitBodyNode.hxx
    include/ast/nodes/HAstInitDeclNode.hxx
    include/ast/nodes/HAstLiteralNode.hxx
    include/ast/nodes/HAstLocalPropertyDeclNode.hxx
    include/ast/nodes/HAstMemberAccessNode.hxx
    include/ast/nodes/HAstModuleDeclNode.hxx
    include/ast/nodes/HAstPropAccessNode.hxx
    include/ast/nodes/HAstPropertyDeclNode.hxx
    include/ast/nodes/HAstReturnNode.hxx
    include/ast/nodes/HAstStatementNode.hxx
    include/ast/nodes/HAstStructBodyNode.hxx
    include/ast/nodes/HAstStructNode.hxx
    include/ast/nodes/HAstTypeNode.hxx
    include/ast/nodes/HAstUnaryExpressionNode.hxx
    include/ast/nodes/HAstVarDeclNode.hxx
    include/ast/nodes/HAstWithAccessLevelNode.hxx
)

add_library(AST STATIC ${HEADERS} src/ast.cxx)

target_include_directories(AST PUBLIC include)
target_include_directories(AST PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(AST PUBLIC Core)