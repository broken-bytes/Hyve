cmake_minimum_required(VERSION 3.26)
cmake_policy(SET CMP0067 NEW)
SET(CXX_STANDARD 23)
SET(CXX_STANDARD_REQUIRED ON)
SET(CXX_EXTENSIONS OFF)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++23" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++23")
    endif()
endif()

project(Hyve)

set_property(GLOBAL PROPERTY CXX_STANDARD 23)

add_subdirectory(core)
add_subdirectory(cli)
add_subdirectory(lexer)
add_subdirectory(parser)
add_subdirectory(typeck)
add_subdirectory(hir)

add_executable(Hyve main.cxx)

set_property(TARGET Core PROPERTY CXX_STANDARD 23)
set_property(TARGET CLI PROPERTY CXX_STANDARD 23)
set_property(TARGET Lexer PROPERTY CXX_STANDARD 23)
set_property(TARGET Parser PROPERTY CXX_STANDARD 23)
set_property(TARGET Typeck PROPERTY CXX_STANDARD 23)
set_property(TARGET Hyve PROPERTY CXX_STANDARD 23)
set_property(TARGET HIR PROPERTY CXX_STANDARD 23)

target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/cli/include)
target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/lexer/include)
target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/parser/include)
target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/typeck/include)
target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/hir/include)
target_include_directories(Hyve PUBLIC ${CMAKE_SOURCE_DIR}/compiler/include)

target_link_libraries(Hyve PUBLIC CLI Lexer Parser Typeck HIR)