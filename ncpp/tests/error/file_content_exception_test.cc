/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "error/file_content_exception.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>

// Menggunakan namespace std::filesystem untuk memudahkan manipulasi file
namespace fs = std::filesystem;

// Test Case untuk FileContentException
class FileContentExceptionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Membuat file teks sementara dengan konten untuk pengujian
        std::ofstream out(validFilePath);
        out << "Ini adalah baris pertama.\n";
        out << "Ini adalah baris kedua.";
        out.close();
    }

    void TearDown() override
    {
        // Menghapus file setelah pengujian
        fs::remove(validFilePath);
    }

private:
    std::string validFilePath = "test_file.txt";           // File yang valid untuk pengujian
    std::string invalidFilePath = "non_existent_file.txt"; // File yang tidak ada

public:
    [[nodiscard]] std::string getValidFilePath() const
    {
        return validFilePath;
    }

    [[nodiscard]] std::string getInvalidFilePath() const
    {
        return invalidFilePath;
    }
};

// Test untuk kasus ketika file tidak ada
TEST_F(FileContentExceptionTest, ThrowsWhenFileDoesNotExist)
{
    ncpp::FileContentException exception(ncpp::FileContentException::ERROR, "Kesalahan membaca file", this->getInvalidFilePath(), "", 1, 1);

    EXPECT_STREQ(exception.what(), "---------------------------------------------\nnon_existent_file.txt:1:1 \033[31mkesalahan\033[0m\n\n1| Tidak dapat menampilkan konten di file 'non_existent_file.txt', karena file tidak ada.\n   ^\nKesalahan membaca file\n\n");
}

// Test untuk kasus ketika file berhasil dibaca
TEST_F(FileContentExceptionTest, ReturnsCorrectMessageWhenFileIsReadSuccessfully)
{
    ncpp::FileContentException exception(ncpp::FileContentException::ERROR, "Kesalahan membaca file", this->getValidFilePath(), "", 1, 5);
    EXPECT_STREQ(exception.what(), "---------------------------------------------\ntest_file.txt:1:5 \033[31mkesalahan\033[0m\n\n1| Ini adalah baris pertama.\n       ^\nKesalahan membaca file\n\n");
}

// Test untuk kasus ketika terjadi kesalahan saat membaca file (misalnya, jika kita mencoba membaca baris yang tidak ada)
TEST_F(FileContentExceptionTest, ThrowsWhenReadingInvalidLine)
{
    ncpp::FileContentException exception(ncpp::FileContentException::WARNING, "Kesalahan membaca file", this->getValidFilePath(), "", 3, 1);
    EXPECT_STREQ(exception.what(), "---------------------------------------------\ntest_file.txt:3:1 \033[33mperingatan\033[0m\n\n3| Tidak dapat menampilkan konten, karena mencoba mengakses baris ke-3, tapi di konten hanya ada 2 baris\n   ^\nKesalahan membaca file\n\n");
}