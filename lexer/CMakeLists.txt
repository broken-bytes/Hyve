SET(
    SRC
    src/HLexer.cxx
    src/HTokenStream.cxx
)

SET(
    HEADERS
    include/lexer/HLexer.hxx
    include/lexer/HTokenStream.hxx
)

add_library(Lexer STATIC ${SRC} ${HEADERS})

target_include_directories(Lexer PUBLIC include)
target_include_directories(Lexer PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Lexer Core)
