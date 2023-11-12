SET(
    SRC
    src/HCLI.cxx
)

add_library(CLI STATIC ${SRC})

target_include_directories(CLI PUBLIC include)