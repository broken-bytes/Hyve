SET(
    SRC
    src/HLexer.cxx
    src/HTokenStream.cxx
    src/processors/HControlFlowProcessor.cxx
    src/processors/HGroupingProcessor.cxx
    src/processors/HIdentifierProcessor.cxx
    src/processors/HKeywordProcessor.cxx
    src/processors/HLiteralProcessor.cxx
    src/processors/HNumberProcessor.cxx
    src/processors/HOperatorProcessor.cxx
    src/processors/HPunctuationProcessor.cxx
    src/processors/HSpecialProcessor.cxx
)

SET(
    HEADERS
    include/lexer/HLexer.hxx
    include/lexer/HLexerError.hxx
    include/lexer/HToken.hxx
    include/lexer/HTokenGroupings.hxx
    include/lexer/HTokenKeywords.hxx
    include/lexer/HTokenOperators.hxx
    include/lexer/HTokenSpecials.hxx
    include/lexer/HTokenStream.hxx
    include/lexer/HTokenType.hxx
    include/lexer/HProcessor.hxx
    include/lexer/processors/HControlFlowProcessor.hxx
    include/lexer/processors/HGroupingProcessor.hxx
    include/lexer/processors/HIdentifierProcessor.hxx
    include/lexer/processors/HKeywordProcessor.hxx
    include/lexer/processors/HLiteralProcessor.hxx
    include/lexer/processors/HNumberProcessor.hxx
    include/lexer/processors/HOperatorProcessor.hxx
    include/lexer/processors/HPunctuationProcessor.hxx
    include/lexer/processors/HSpecialProcessor.hxx
)

add_library(Lexer STATIC ${SRC} ${HEADERS})


target_include_directories(Lexer PUBLIC include)
target_include_directories(Lexer PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Lexer Core)
