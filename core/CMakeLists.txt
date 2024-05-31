SET(
    SRC
    src/Core.cxx
)

SET(
    HEADERS
    include/core/HAccessLevel.hxx
    include/core/HCompilerError.hxx
)

add_library(Core STATIC ${SRC} ${HEADERS})

target_include_directories(Core PUBLIC include)