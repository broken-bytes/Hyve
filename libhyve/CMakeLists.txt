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
target_include_directories(libhyve PUBLIC ${CMAKE_SOURCE_DIR}/generator/include)

target_link_libraries(libhyve PRIVATE Typeck Parser Lexer AST Generator Core)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_AVAILABLE_LIBS}")
message(Status "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")
message(Status "LLVM Definitions: ${LLVM_DEFINITIONS}")

# Include LLMV
target_include_directories(libhyve PUBLIC ${LLVM_INCLUDE_DIRS})

# Link LLVM
target_link_directories(libhyve PRIVATE ${LLVM_LIBRARY_DIRS})
