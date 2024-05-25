SET(
    SRC
    src/HIRTransformer.cxx
)

add_library(HIR STATIC ${SRC})

target_include_directories(HIR PUBLIC include)
target_include_directories(HIR PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)