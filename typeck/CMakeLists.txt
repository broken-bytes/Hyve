SET(
    SRC
    src/HTypeck.cxx
)

add_library(Typeck STATIC ${SRC})

target_include_directories(Typeck PUBLIC include)
target_include_directories(Typeck PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)