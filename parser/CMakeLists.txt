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
)

add_library(Parser STATIC ${SRC} ${HEADERS})

target_include_directories(Parser PUBLIC include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/ast/include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/lexer/include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Parser PUBLIC Core AST)