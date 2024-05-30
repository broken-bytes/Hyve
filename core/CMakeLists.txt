SET(
    SRC
    src/Core.cxx
)

add_library(Core STATIC ${SRC})

target_include_directories(Core PUBLIC include)