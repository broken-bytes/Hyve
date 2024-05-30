SET(
    SRC
    src/HParser.cxx
)

add_library(Parser STATIC ${SRC})

target_include_directories(Parser PUBLIC include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/lexer/include)
target_include_directories(Parser PUBLIC ${CMAKE_SOURCE_DIR}/core/include)

target_link_libraries(Parser PUBLIC Core)