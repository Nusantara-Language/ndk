/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef FILE_CONTENT_EXCEPTION_H
#define FILE_CONTENT_EXCEPTION_H

#include <exception>
#include <ostream>
#include <string>

namespace ncpp {

/**
 * @brief Kelas FileContentException adalah pengecualian yang digunakan untuk menangani kesalahan terkait konten file.
 *
 * Kelas ini menyimpan informasi tentang kesalahan yang terjadi saat membaca konten dari file,
 * termasuk pesan kesalahan, jalur file, konten yang relevan, serta posisi baris dan kolom
 * di mana kesalahan terjadi.
 */
class FileContentException : public std::exception
{
public:
    enum Type
    {
        WARNING,
        ERROR
    };

    /**
     * @brief Konstruktor untuk FileContentException.
     *
     * @param message Pesan kesalahan yang menjelaskan masalah.
     * @param filepath Jalur file tempat kesalahan terjadi.
     * @param content Konten yang relevan dari file.
     * @param row Baris di mana kesalahan terjadi.
     * @param column Kolom di mana kesalahan terjadi.
     */
    FileContentException(const Type& type, std::string message, std::string filepath, std::string content, const size_t& row = 0, const size_t& column = 0);

    /**
     * @brief Mengembalikan pesan kesalahan yang telah diformat.
     *
     * Metode ini akan mencoba membaca konten dari file dan menyusun pesan kesalahan
     * yang lebih informatif berdasarkan posisi baris dan kolom. Jika file tidak ada atau
     * terjadi kesalahan saat membaca, metode ini akan mengembalikan pesan kesalahan yang sesuai.
     *
     * @return Pesan kesalahan dalam bentuk string.
     */
    [[nodiscard]] const char* what() const noexcept override;

    /**
     * @brief Operator overload untuk mencetak objek FileContentException ke output stream.
     *
     * Fungsi ini memungkinkan objek dari kelas FileContentException untuk dicetak langsung ke
     * output stream (seperti std::cout) dengan memanggil metode what() dari objek tersebut.
     * Ini memudahkan dalam debugging dan logging informasi kesalahan yang terkait dengan
     * konten file.
     *
     * @param os Output stream yang digunakan untuk mencetak informasi kesalahan.
     *           Ini biasanya adalah std::cout atau output stream lainnya.
     * @param fce Objek dari kelas FileContentException yang ingin dicetak.
     *           Ini berisi informasi tentang kesalahan yang terjadi saat memproses konten file.
     * @return std::ostream& Mengembalikan referensi ke output stream yang sama,
     *         memungkinkan chaining dari operasi output.
     */
    inline friend std::ostream& operator<<(std::ostream& os, const FileContentException& fce)
    {
        // Memanggil metode what() dari objek fce untuk mendapatkan pesan kesalahan
        os << fce.what();

        // Mengembalikan referensi ke output stream untuk memungkinkan chaining
        return os;
    }

    // akhir dari access modifiers public

private:
    mutable bool isExceptionMessageReady = false; ///< Menandakan apakah pesan kesalahan sudah disiapkan.
    mutable std::string message;                  ///< Pesan kesalahan asli.
    std::string filepath;                         ///< Jalur file yang terlibat dalam kesalahan.
    std::string content;                          ///< Konten relevan dari file.
    size_t column;                                ///< Kolom di mana kesalahan terjadi.
    size_t row;                                   ///< Baris di mana kesalahan terjadi.
    Type type;                                    ///< Tipe kesalahan.
    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class FileContentException

} // namespace ncpp

#endif