/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "error/file_content_exception.h"
#include "file/file_txt.h"
#include <cstddef>
#include <exception>
#include <format>
#include <string>
#include <utility>

namespace ncpp {

/**
 * @brief Konstruktor untuk FileContentException.
 *
 * @param message Pesan kesalahan yang menjelaskan masalah.
 * @param filepath Jalur file tempat kesalahan terjadi.
 * @param content Konten yang relevan dari file.
 * @param row Baris di mana kesalahan terjadi.
 * @param column Kolom di mana kesalahan terjadi.
 */
FileContentException::FileContentException(const Type& type, std::string message, std::string filepath, std::string content, const size_t& row, const size_t& column) : type(type), message(std::move(message)), filepath(std::move(filepath)), content(std::move(content)), row(row), column(column) {}

/**
 * @brief Mengembalikan pesan kesalahan yang telah diformat.
 *
 * Metode ini akan mencoba membaca konten dari file dan menyusun pesan kesalahan
 * yang lebih informatif berdasarkan posisi baris dan kolom. Jika file tidak ada atau
 * terjadi kesalahan saat membaca, metode ini akan mengembalikan pesan kesalahan yang sesuai.
 *
 * @return Pesan kesalahan dalam bentuk string.
 */
const char* FileContentException::what() const noexcept
{
    // Memeriksa apakah pesan kesalahan sudah disiapkan sebelumnya
    if (!isExceptionMessageReady)
    {
        std::string msgResultTemp; // Variabel untuk menyimpan pesan hasil
        std::string ctnInFle;      // Variabel untuk menyimpan konten dari file

        try
        {
            ncpp::FileTxt file(filepath); // Membuat objek FileTxt untuk membaca file
            // Memeriksa apakah file ada
            if (!file.exist())
            {
                // Jika file tidak ada, siapkan pesan kesalahan yang sesuai
                ctnInFle = std::format("Tidak dapat menampilkan konten di file '{}', karena file tidak ada.", filepath);
            }
            else
            {
                // Jika file ada, baca kontennya
                file.read();
                ctnInFle = file.getContentInLine(std::max(0, static_cast<int>(row) - 1)); // Ambil konten pada baris yang relevan
            }
        }
        catch (const std::exception& error)
        {
            // Menangkap pengecualian jika terjadi kesalahan saat membaca file
            ctnInFle = std::format("Tidak dapat menampilkan konten, karena {}", error.what());
        }

        std::string prefix = std::format("{}| ", row);                                   // Membuat prefix untuk menandai baris
        int arrowSpace = static_cast<int>(prefix.size()) + static_cast<int>(column) - 1; // Menghitung spasi untuk panah

        // Menyusun pesan hasil
        msgResultTemp += "---------------------------------------------\n";
        msgResultTemp += std::format("{}:{}:{} {}\n\n", filepath, row, column, this->type == ERROR ? "\033[31mkesalahan\033[0m" : "\033[33mperingatan\033[0m"); // Menambahkan informasi lokasi kesalahan
        msgResultTemp += std::format("{}{}\n", prefix, ctnInFle);                                                                                               // Menambahkan konten dari file
        msgResultTemp += std::format("{}{}\n", std::string(arrowSpace, ' '), std::string(std::max(1, static_cast<int>(content.size())), '^'));                  // Menambahkan panah penunjuk
        msgResultTemp += std::format("{}\n\n", message);                                                                                                        // Menambahkan pesan kesalahan asli

        // Simpan pesan hasil ke dalam variabel message
        message = std::move(msgResultTemp);
        isExceptionMessageReady = true; // Tandai bahwa pesan sudah siap untuk ditampilkan
    }

    return message.c_str(); // Mengembalikan pointer ke pesan kesalahan yang telah diformat
}

} // namespace ncpp