/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "string/string.h"
#include <gtest/gtest.h>

// Unit test untuk fungsi trim
TEST(StringTest, TrimEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::trim(input), "");
}

TEST(StringTest, TrimOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::trim(input), "");
}

TEST(StringTest, TrimLeadingWhitespace)
{
    std::string input = "   Hello World!   ";
    EXPECT_EQ(ncpp::trim(input), "Hello World!");
}

TEST(StringTest, TrimTrailingWhitespace)
{
    std::string input = "   Hello World!   ";
    EXPECT_EQ(ncpp::trim(input), "Hello World!");
}

TEST(StringTest, TrimNoWhitespace)
{
    std::string input = "HelloWorld!";
    EXPECT_EQ(ncpp::trim(input), "HelloWorld!");
}

TEST(StringTest, TrimMixedWhitespace)
{
    std::string input = "\t Hello \n World! \r";
    EXPECT_EQ(ncpp::trim(input), "Hello \n World!");
}

// Unit test untuk fungsi lTrim
TEST(StringTest, LTrimEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::lTrim(input), "");
}

TEST(StringTest, LTrimOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::lTrim(input), "");
}

TEST(StringTest, LTrimLeadingWhitespace)
{
    std::string input = "   Hello World!";
    EXPECT_EQ(ncpp::lTrim(input), "Hello World!");
}

TEST(StringTest, LTrimNoLeadingWhitespace)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::lTrim(input), "Hello World!");
}

TEST(StringTest, LTrimMixedWhitespace)
{
    std::string input = "\t   Hello World!";
    EXPECT_EQ(ncpp::lTrim(input), "Hello World!");
}

TEST(StringTest, LTrimWhitespaceOnlyAtStart)
{
    std::string input = "   ";
    EXPECT_EQ(ncpp::lTrim(input), "");
}

// Unit test untuk fungsi rTrim
TEST(StringTest, RTrimEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::rTrim(input), "");
}

TEST(StringTest, RTrimOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::rTrim(input), "");
}

TEST(StringTest, RTrimTrailingWhitespace)
{
    std::string input = "Hello World!   ";
    EXPECT_EQ(ncpp::rTrim(input), "Hello World!");
}

TEST(StringTest, RTrimNoTrailingWhitespace)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::rTrim(input), "Hello World!");
}

TEST(StringTest, RTrimMixedWhitespace)
{
    std::string input = "Hello World! \t\n\r";
    EXPECT_EQ(ncpp::rTrim(input), "Hello World!");
}

TEST(StringTest, RTrimWhitespaceOnlyAtEnd)
{
    std::string input = "   ";
    EXPECT_EQ(ncpp::rTrim(input), "");
}

// Unit test untuk fungsi trimmed
TEST(StringTest, TrimmedEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::trimmed(input), "");
}

TEST(StringTest, TrimmedOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::trimmed(input), "");
}

TEST(StringTest, TrimmedLeadingAndTrailingWhitespace)
{
    std::string input = "   Hello World!   ";
    EXPECT_EQ(ncpp::trimmed(input), "Hello World!");
}

TEST(StringTest, TrimmedNoWhitespace)
{
    std::string input = "HelloWorld!";
    EXPECT_EQ(ncpp::trimmed(input), "HelloWorld!");
}

// Unit test untuk fungsi lTrimmed
TEST(StringTest, LTrimmedEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::lTrimmed(input), "");
}

TEST(StringTest, LTrimmedOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::lTrimmed(input), "");
}

TEST(StringTest, LTrimmedLeadingWhitespace)
{
    std::string input = "   Hello World!";
    EXPECT_EQ(ncpp::lTrimmed(input), "Hello World!");
}

TEST(StringTest, LTrimmedNoLeadingWhitespace)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::lTrimmed(input), "Hello World!");
}

// Unit test untuk fungsi rTrimmed
TEST(StringTest, RTrimmedEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::rTrimmed(input), "");
}

TEST(StringTest, RTrimmedOnlyWhitespace)
{
    std::string input = "   \t\n\r   ";
    EXPECT_EQ(ncpp::rTrimmed(input), "");
}

TEST(StringTest, RTrimmedTrailingWhitespace)
{
    std::string input = "Hello World!   ";
    EXPECT_EQ(ncpp::rTrimmed(input), "Hello World!");
}

TEST(StringTest, RTrimmedNoTrailingWhitespace)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::rTrimmed(input), "Hello World!");
}

// Unit test untuk fungsi splitView
TEST(StringTest, SplitViewEmptyString)
{
    std::string_view input;
    auto result = ncpp::splitView(input, ',', false);
    EXPECT_TRUE(result.empty());
}

TEST(StringTest, SplitViewOnlyDelimiter)
{
    std::string_view input = "|||";
    auto result = ncpp::splitView(input, '|', false);
    EXPECT_TRUE(result.empty());
}

TEST(StringTest, SplitViewSingleToken)
{
    std::string_view input = "Hello";
    auto result = ncpp::splitView(input, ',', false);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "Hello");
}

TEST(StringTest, SplitViewMultipleTokens)
{
    std::string_view input = "Hello,World,Test";
    auto result = ncpp::splitView(input, ',', false);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
    EXPECT_EQ(result[2], "Test");
}

TEST(StringTest, SplitViewTrailingDelimiter)
{
    std::string_view input = "Hello,World,";
    auto result = ncpp::splitView(input, ',', false);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
}

TEST(StringTest, SplitViewLeadingDelimiter)
{
    std::string_view input = ",Hello,World";
    auto result = ncpp::splitView(input, ',', false);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
}

TEST(StringTest, SplitViewKeepEmptyTokens)
{
    std::string_view input = ",Hello,,World,,";
    auto result = ncpp::splitView(input, ',', true);
    ASSERT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "Hello");
    EXPECT_EQ(result[2], "");
    EXPECT_EQ(result[3], "World");
    EXPECT_EQ(result[4], "");
    EXPECT_EQ(result[5], "");
}

// Unit test untuk fungsi split
TEST(StringTest, SplitEmptyString)
{
    std::string input;
    auto result = ncpp::split(input, ',', false);
    EXPECT_TRUE(result.empty());
}

TEST(StringTest, SplitOnlyDelimiter)
{
    std::string input = "|||";
    auto result = ncpp::split(input, '|', false);
    EXPECT_TRUE(result.empty());
}

TEST(StringTest, SplitSingleToken)
{
    std::string input = "Hello";
    auto result = ncpp::split(input, ',', false);
    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "Hello");
}

TEST(StringTest, SplitMultipleTokens)
{
    std::string input = "Hello,World,Test";
    auto result = ncpp::split(input, ',', false);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
    EXPECT_EQ(result[2], "Test");
}

TEST(StringTest, SplitTrailingDelimiter)
{
    std::string input = "Hello,World,";
    auto result = ncpp::split(input, ',', false);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
}

TEST(StringTest, SplitLeadingDelimiter)
{
    std::string input = ",Hello,World";
    auto result = ncpp::split(input, ',', false);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "Hello");
    EXPECT_EQ(result[1], "World");
}

TEST(StringTest, SplitKeepEmptyTokens)
{
    std::string input = ",Hello,,World,,";
    auto result = ncpp::split(input, ',', true);

    // Mengharapkan 6 token: "", "Hello", "", "World", "", ""
    ASSERT_EQ(result.size(), 6);
    EXPECT_EQ(result[0], "");
    EXPECT_EQ(result[1], "Hello");
    EXPECT_EQ(result[2], "");
    EXPECT_EQ(result[3], "World");
    EXPECT_EQ(result[4], "");
    EXPECT_EQ(result[5], "");
}

// Unit test untuk fungsi join
TEST(StringTest, JoinMixedCharacters)
{
    std::vector<char> input = {'C', '+', '+', ' ', 'R', 'o', 'c', 'k'};
    EXPECT_EQ(ncpp::join(input), "C++ Rock");
}

TEST(StringTest, JoinEmptyVector)
{
    std::vector<std::string> input;
    EXPECT_EQ(ncpp::join(input, ','), "");

    std::vector<char> inputVecChar;
    EXPECT_EQ(ncpp::join(inputVecChar), "");
}

TEST(StringTest, JoinSingleElement)
{
    std::vector<std::string> input = {"Hello"};
    EXPECT_EQ(ncpp::join(input, ','), "Hello");

    std::vector<char> inputVecChar = {'A'};
    EXPECT_EQ(ncpp::join(inputVecChar), "A");
}

TEST(StringTest, JoinMultipleElements)
{
    std::vector<std::string> input = {"Hello", "World", "Test"};
    EXPECT_EQ(ncpp::join(input, ' '), "Hello World Test");

    std::vector<char> inputVecChar = {'H', 'e', 'l', 'l', 'o'};
    EXPECT_EQ(ncpp::join(inputVecChar), "Hello");
}

TEST(StringTest, JoinDelimiterAtEnd)
{
    std::vector<std::string> input = {"One", "Two", "Three"};
    EXPECT_EQ(ncpp::join(input, '-'), "One-Two-Three");
}

// Unit test untuk fungsi normalize
TEST(StringTest, NormalizeEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::normalize(input), "");
}

TEST(StringTest, NormalizeNoCarriageReturn)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::normalize(input), "Hello World!");
}

TEST(StringTest, NormalizeCarriageReturnOnly)
{
    std::string input = "\r";
    EXPECT_EQ(ncpp::normalize(input), "\n");
}

TEST(StringTest, NormalizeCarriageReturnFollowedByNewline)
{
    std::string input = "\r\n";
    EXPECT_EQ(ncpp::normalize(input), "\n");
}

TEST(StringTest, NormalizeMultipleCarriageReturns)
{
    std::string input = "Line 1\rLine 2\r\nLine 3\r";
    EXPECT_EQ(ncpp::normalize(input), "Line 1\nLine 2\nLine 3\n");
}

TEST(StringTest, NormalizeMixedContent)
{
    std::string input = "Line 1\r\nLine 2\rLine 3";
    EXPECT_EQ(ncpp::normalize(input), "Line 1\nLine 2\nLine 3");
}

// Unit test untuk fungsi normalized
TEST(StringTest, NormalizedEmptyString)
{
    std::string input;
    EXPECT_EQ(ncpp::normalized(input), "");
}

TEST(StringTest, NormalizedNoCarriageReturn)
{
    std::string input = "Hello World!";
    EXPECT_EQ(ncpp::normalized(input), "Hello World!");
}

TEST(StringTest, NormalizedWithCarriageReturns)
{
    std::string input = "Line 1\rLine 2\r\nLine 3\r";
    EXPECT_EQ(ncpp::normalized(input), "Line 1\nLine 2\nLine 3\n");
}