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

target_link_libraries(Generator Core)
