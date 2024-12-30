/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "file/nnmap.h"
#include <fstream>
#include <gtest/gtest.h>
#include <string>
#include <vector>

// Helper function to create a temporary file for testing
void createTempFile(const std::string& filename, const std::string& content)
{
    std::ofstream ofs(filename);
    ofs << content;
    ofs.close();
}

// Unit test for nnmap
TEST(NNMapTest, ReadExistingFile)
{
    // Create a temporary file with known content
    std::string filename = "testfile.txt";
    std::string content = "Hello, World!";
    createTempFile(filename, content);

    // Use nnmap to read the file
    std::vector<char> result = ncpp::nnmap(filename);

    // Check that the content is correct
    EXPECT_EQ(result.size(), content.size());
    EXPECT_EQ(std::string(result.begin(), result.end()), content);

    // Clean up the temporary file
    std::remove(filename.c_str());
}

TEST(NNMapTest, FileNotFound)
{
    // Try to read a non-existent file
    std::string filename = "non_existent_file.txt";

    // Expect an exception to be thrown
    EXPECT_THROW(ncpp::nnmap(filename), std::runtime_error);
}

TEST(NNMapTest, EmptyFile)
{
    // Create a temporary empty file
    std::string filename = "emptyfile.txt";
    createTempFile(filename, "");

    // Expect an exception to be thrown when trying to map an empty file.
    EXPECT_THROW(ncpp::nnmap(filename), std::runtime_error);

    // Clean up the temporary empty file
    std::remove(filename.c_str());
}