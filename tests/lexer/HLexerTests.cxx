#include "lexer/HLexer.hxx"
#include "lexer/HToken.hxx"
#include "lexer/HTokenStream.hxx"
#include "lexer/HTokenType.hxx"
#include <catch2/catch_test_macros.hpp>

using namespace Hyve::Lexer;

TEST_CASE("HLexer - Empty", "Tokenize_EmptyString") {
    HLexer lexer;
    auto tokenStream = lexer.Tokenize("", "testfile");

    auto token = tokenStream.Begin();

    REQUIRE(token != tokenStream.End());
    REQUIRE(token->Type == HTokenType::END_OF_FILE);
}

using namespace Hyve::Lexer;

// ... your header files here

TEST_CASE("HLexer - Keywords", "[lexer][keywords]") {
    using enum HTokenType;
    using enum HTokenFamily;
    HLexer lexer;
    HTokenStream stream = lexer.Tokenize("class fn let module struct var public if else", "test.hy");

    std::vector<HToken> expectedTokens = {
        {KEYWORD, CLASS},
        {KEYWORD, FUNC},
        {KEYWORD, LET},
        {KEYWORD, MODULE},
        {KEYWORD, STRUCT},
        {KEYWORD, VAR},
        {KEYWORD, PUBLIC},
        {KEYWORD, IF},
        {KEYWORD, ELSE},
        {UNKNOWN, END_OF_FILE}
    };

    REQUIRE(stream.Begin() != stream.End()); // Ensure there are tokens
    for (const HToken& expected : expectedTokens) {
        HToken actual = stream.Consume();
        REQUIRE(actual.Family == expected.Family);
        REQUIRE(actual.Type == expected.Type);
    }
}

TEST_CASE("HLexer - Identifiers", "[lexer][identifiers]") {
    using enum HTokenType;
    using enum HTokenFamily;

    HLexer lexer;
    HTokenStream stream = lexer.Tokenize("myVar _myVar myVar123", "test.hy");

    std::vector<HTokenType> expectedTypes = {
        IDENTIFIER, IDENTIFIER, IDENTIFIER, END_OF_FILE
    };

    REQUIRE(stream.Begin() != stream.End());
    for (const HTokenType& expectedType : expectedTypes) {
        HToken actual = stream.Consume();
        REQUIRE(actual.Type == expectedType);
    }
}

TEST_CASE("HLexer - Identifiers", "[lexer][numeric literals]") {
    using enum HTokenType;
    using enum HTokenFamily;

    HLexer lexer;
    HTokenStream stream = lexer.Tokenize("0.0 0x2 0b1 200 -300", "test.hy");

    std::vector<HTokenType> expectedTypes = {
        NUM, NUM, NUM, NUM, NUM, END_OF_FILE
    };

    REQUIRE(stream.Begin() != stream.End());
    for (const HTokenType& expectedType : expectedTypes) {
        HToken actual = stream.Consume();
        REQUIRE(actual.Type == expectedType);
    }
}