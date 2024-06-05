SET(
    SRC
    src/HParser.cxx
    src/IHParser.cxx
    src/parsers/HClassParser.cxx
    src/parsers/HEnumParser.cxx
    src/parsers/HExpressionParser.cxx
    src/parsers/HFuncParser.cxx
    src/parsers/HInheritanceParser.cxx
    src/parsers/HInitParser.cxx
    src/parsers/HModuleParser.cxx
    src/parsers/HPropertyParser.cxx
    src/parsers/HProtocolParser.cxx
    src/parsers/HPrototypeParser.cxx
    src/parsers/HStatementParser.cxx
    src/parsers/HStructParser.cxx
    src/parsers/HTypeParser.cxx
    src/parsers/HVariableParser.cxx
)

SET(
    HEADERS
    include/parser/HParser.hxx
    include/parser/IHParser.hxx
    include/parser/HAst.hxx
    include/parser/HAstNode.hxx
    include/parser/HAstNodeType.hxx
    include/parser/HAstOperatorType.hxx
    include/parser/HAstParameter.hxx
    include/parser/HParserContext.hxx
    include/parser/parsers/HClassParser.hxx
    include/parser/parsers/HEnumParser.hxx
    include/parser/parsers/HExpressionParser.hxx
    include/parser/parsers/HFuncParser.hxx
    include/parser/parsers/HInheritanceParser.hxx
    include/parser/parsers/HInitParser.hxx
    include/parser/parsers/HModuleParser.hxx
    include/parser/parsers/HPropertyParser.hxx
    include/parser/parsers/HProtocolParser.hxx
    include/parser/parsers/HPrototypeParser.hxx
    include/parser/parsers/HStatementParser.hxx
    include/parser/parsers/HStructParser.hxx
    include/parser/parsers/HTypeParser.hxx
    include/parser/parsers/HVariableParser.hxx
    include/parser/nodes/HAstArrayNode.hxx
    include/parser/nodes/HAstAssignmentNode.hxx
    include/parser/nodes/HAstBinaryExpressionNode.hxx
    include/parser/nodes/HAstBlockNode.hxx
    include/parser/nodes/HAstClassBodyNode.hxx
    include/parser/nodes/HAstClassNode.hxx
    include/parser/nodes/HAstExpressionNode.hxx
    include/parser/nodes/HAstFileNode.hxx
    include/parser/nodes/HAstFuncCallNode.hxx
    include/parser/nodes/HAstImportNode.hxx
    include/parser/nodes/HAstInheritanceNode.hxx
    include/parser/nodes/HAstInitBodyNode.hxx
    include/parser/nodes/HAstInitDeclNode.hxx
    include/parser/nodes/HAstLiteralNode.hxx
    include/parser/nodes/HAstLocalPropertyDeclNode.hxx
    include/parser/nodes/HAstMemberAccessNode.hxx
    include/parser/nodes/HAstModuleDeclNode.hxx
    include/parser/nodes/HAstPropAccessNode.hxx
    include/parser/nodes/HAstPropertyDeclNode.hxx
    include/parser/nodes/HAstProtocolBodyNode.hxx
    include/parser/nodes/HAstProtocolNode.hxx
    include/parser/nodes/HAstPrototypeBodyNode.hxx
    include/parser/nodes/HAstPrototypeNode.hxx
    include/parser/nodes/HAstReturnNode.hxx
    include/parser/nodes/HAstStatementNode.hxx
    include/parser/nodes/HAstStructBodyNode.hxx
    include/parser/nodes/HAstStructNode.hxx
    include/parser/nodes/HAstTypeNode.hxx
    include/parser/nodes/HAstUnaryExpressionNode.hxx
    include/parser/nodes/HAstVarDeclNode.hxx
    include/parser/nodes/HAstWithAccessLevelNode.hxx
)

add_library(Parser STATIC ${SRC} ${HEADERS})

target_include_directories(Parser PUBLIC include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/lexer/include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Parser PUBLIC Core)