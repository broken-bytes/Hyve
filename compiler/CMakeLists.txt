SET(
    SRC
    src/HCompiler.cxx
)

add_library(Compiler STATIC ${SRC})

target_include_directories(Compiler PUBLIC include)