add_executable(hyvec src/main.cxx)

target_include_directories(hyvec PUBLIC ${CMAKE_SOURCE_DIR}/cli/include)

target_link_libraries(hyvec PUBLIC CLI)