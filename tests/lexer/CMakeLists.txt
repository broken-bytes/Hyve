# --- TESTS ---

set(TEST_SOURCES
    HLexerTests.cxx
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
add_executable(HLexerTest ${TEST_SOURCES})

# Set the C++ standard
set_property(TARGET HLexerTest PROPERTY CXX_STANDARD 23)

# Include directories
target_include_directories(HLexerTest PRIVATE ${CMAKE_SOURCE_DIR}/lexer/include)

# Link GoogleTest to the test executable
target_link_libraries(HLexerTest Lexer Catch2::Catch2WithMain)

# Add a test
add_test(NAME HLexerTest COMMAND HLexerTest)

set_target_properties(HLexerTest PROPERTIES FOLDER "tests")