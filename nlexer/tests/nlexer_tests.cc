#include "nlexer.h"
#include "ntoken.h"
#include <gtest/gtest.h>

// Helper function to create a lexer and process input
nlexer::NToken::Wrapper getTokensFromInput(const std::string& input, const std::shared_ptr<std::vector<nlexer::NToken::Wrapper>>& twraps)
{
    nlexer::NLexer lexer(twraps);
    return lexer.input(input); // Proses input menjadi token
}

// Test case for a simple input
TEST(NLexerTest, SimpleInput)
{
    auto twraps = std::make_shared<std::vector<nlexer::NToken::Wrapper>>();
    nlexer::NToken::Wrapper tokens = getTokensFromInput("muat 'halodunia.n'", twraps);

    ASSERT_EQ(twraps->size(), 1);       // Pastikan satu wrapper token dihasilkan
    ASSERT_EQ(tokens.tokens.size(), 3); // Harapkan 2 token: LOAD_FILE_KEYWORD, STRING, NEOF

    EXPECT_EQ(tokens.tokens[0].type, nlexer::NToken::LOAD_FILE_KEYWORD);
    EXPECT_EQ(tokens.tokens[1].type, nlexer::NToken::STRING);
    EXPECT_EQ(tokens.tokens[2].type, nlexer::NToken::NEOF);
}

// Test case for unrecognized token
TEST(NLexerTest, UnrecognizedToken)
{
    auto twraps = std::make_shared<std::vector<nlexer::NToken::Wrapper>>();
    nlexer::NToken::Wrapper tokens = getTokensFromInput("?", twraps);
    ASSERT_EQ(twraps->size(), 1);       // Pastikan satu wrapper token dihasilkan
    ASSERT_EQ(tokens.tokens.size(), 2); // Harapkan 1 token: UNKNOWN, NEOF

    EXPECT_EQ(tokens.tokens[0].type, nlexer::NToken::UNKNOWN);
    EXPECT_EQ(tokens.tokens[1].type, nlexer::NToken::NEOF);
}

// Test case for newline handling
TEST(NLexerTest, NewlineHandling)
{
    auto twraps = std::make_shared<std::vector<nlexer::NToken::Wrapper>>();
    nlexer::NToken::Wrapper tokens = getTokensFromInput("nama\n'Fern Aerell'", twraps);

    ASSERT_EQ(twraps->size(), 1);       // Pastikan satu wrapper token dihasilkan
    ASSERT_EQ(tokens.tokens.size(), 3); // Harapkan 2 token: ID, STRING, NEOF

    EXPECT_EQ(tokens.tokens[0].type, nlexer::NToken::ID);
    EXPECT_EQ(tokens.tokens[1].type, nlexer::NToken::STRING);
    EXPECT_EQ(tokens.tokens[2].type, nlexer::NToken::NEOF);
}

// Main function to run all tests
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}