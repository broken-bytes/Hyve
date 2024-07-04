SET(
    SRC
    src/HCompiler.cxx
)

SET(
    HEADERS
    include/libhyve/HCompiler.hxx
    include/libhyve/HCompilerArgument.hxx
)

add_library(libhyve STATIC ${SRC} ${HEADERS})

target_include_directories(libhyve PUBLIC include)
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/typeck/include)
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/lexer/include)
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(libhyve PUBLIC Typeck Parser Lexer Core)

# TESTING ONLY
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/generator/include)
target_link_libraries(libhyve PUBLIC Generator)