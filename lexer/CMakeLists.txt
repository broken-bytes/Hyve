SET(
    SRC
    src/HLexer.cxx
    src/HTokenStream.cxx
)

add_library(Lexer STATIC ${SRC})

target_include_directories(Lexer PUBLIC include)