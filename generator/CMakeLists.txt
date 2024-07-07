SET(
    SRC
    src/HGenerator.cxx
)

SET(
    HEADERS
    include/generator/HGenerator.hxx
)

add_library(Generator STATIC ${SRC} ${HEADERS})

target_include_directories(Generator PUBLIC include)
target_include_directories(Generator PUBLIC ${CMAKE_SOURCE_DIR}/core/include)
target_include_directories(Generator PUBLIC ${CMAKE_SOURCE_DIR}/ast/include)

target_link_libraries(Generator PUBLIC AST Core)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_AVAILABLE_LIBS}")
message(Status "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")
message(Status "LLVM Definitions: ${LLVM_DEFINITIONS}")

# Include LLMV
target_include_directories(Generator PUBLIC ${LLVM_INCLUDE_DIRS})

# Link LLVM
target_link_directories(Generator PRIVATE ${LLVM_LIBRARY_DIRS})

llvm_map_components_to_libnames(llvm_libs
    Core
    Support
    IRReader
    X86AsmParser
    X86CodeGen
    X86Desc
    X86Disassembler
    X86Info
    Linker
    # Add other components as needed
)

target_link_libraries(Generator PUBLIC ${llvm_libs})

if(WIN32)
    target_link_libraries(Generator PUBLIC shlwapi Ws2_32)
endif()

set(PROPERTY CMAKE_INTERPROCEDURAL_OPTIMIZATION OFF)


