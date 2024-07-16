SET(
    SRC
    src/HMangler.cxx
)

SET(
    HEADERS
    include/mangler/HMangler.hxx
)

add_library(Mangler STATIC ${SRC} ${HEADERS})

target_include_directories(Mangler PUBLIC include)
target_include_directories(Mangler PUBLIC ${CMAKE_SOURCE_DIR}/core/include)
target_include_directories(Mangler PUBLIC ${CMAKE_SOURCE_DIR}/ast/include)

target_link_libraries(Mangler PUBLIC AST Core)
