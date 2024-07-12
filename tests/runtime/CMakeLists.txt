# --- TESTS ---

set(TEST_SOURCES
    HRuntimeTests.cxx
)

# Add GoogleTest
# You can use the system-installed version or add it as a submodule
# Here we use FetchContent to download it
Include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.6.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# Add the executable for tests
add_executable(HRuntimeTest ${TEST_SOURCES})

# Set the C++ standard
set_property(TARGET HRuntimeTest PROPERTY CXX_STANDARD 23)

# Include directories
target_include_directories(HRuntimeTest PRIVATE ${CMAKE_SOURCE_DIR}/runtime/include)

# Link GoogleTest to the test executable
target_link_libraries(HRuntimeTest Runtime Catch2::Catch2WithMain)

# Add a test
add_test(NAME HRuntimeTest COMMAND HRuntimeTest)

set_target_properties(HRuntimeTest PROPERTIES FOLDER "tests")

if (CMAKE_IMPORT_LIBRARY_SUFFIX)
    add_custom_command(
        TARGET HRuntimeTest POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:HRuntimeTest> $<TARGET_FILE_DIR:HRuntimeTest>
        COMMAND_EXPAND_LISTS
    )
endif ()