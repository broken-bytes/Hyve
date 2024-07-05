SET(
    SRC
    src/HCLI.cxx
)

SET(
    HEADERS
    include/cli/HCLI.hxx
    include/cli/HCLICommand.hxx
    include/cli/HCLICommandParameter.hxx
    include/cli/HCLIInvalidCommandException.hxx
)

add_library(CLI STATIC ${SRC} ${HEADERS})

target_include_directories(CLI PUBLIC include)
target_include_directories(CLI PUBLIC ${CMAKE_SOURCE_DIR}/libhyve/include)

target_link_libraries(CLI PUBLIC libhyve)
