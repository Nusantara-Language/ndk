/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NLEXER_H
#define NLEXER_H

#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "ntoken.h"

namespace nlexer {

class NLexer
{
public:
    /**
     * @brief Konstruktor untuk kelas NLexer.
     *
     * Menerima shared pointer ke vector yang berisi Wrapper token.
     *
     * @param twraps Shared pointer ke vector yang menyimpan Wrapper token.
     */
    explicit NLexer(const std::shared_ptr<std::vector<NToken::Wrapper>>& twraps);

    /**
     * @brief Memproses input string dan menghasilkan token.
     *
     * Fungsi ini menerima string input dan lokasi opsional, kemudian
     * memanggil fungsi tokenization untuk memproses input menjadi token.
     *
     * @param input String yang berisi konten yang akan diproses.
     * @param path Lokasi file (opsional) untuk referensi kesalahan.
     * @return Referensi ke Wrapper token yang dihasilkan.
     */
    NToken::Wrapper& input(const std::string& input, const std::string& path = "");

    /**
     * @brief Memproses konten dari file dan menghasilkan token.
     *
     * Fungsi ini membaca konten dari file yang diberikan dan memanggil fungsi
     * input untuk memproses konten tersebut menjadi token. Jika file tidak ada,
     * akan melempar pengecualian.
     *
     * @param path Lokasi file yang akan dibaca.
     * @return Referensi ke Wrapper token yang dihasilkan.
     */
    NToken::Wrapper& inputFile(const std::string& path);

private:
    std::shared_ptr<std::vector<NToken::Wrapper>> twraps; ///< Pointer bersama ke vector yang menyimpan wrapper token yang dihasilkan.

    /**
     * @brief Melakukan tokenisasi pada konten string.
     *
     * Fungsi ini memproses konten string menjadi daftar token. Jika ditemukan
     * bagian yang tidak dikenali, akan mencetak pesan kesalahan. Menambahkan
     * token EOF di akhir daftar token.
     *
     * @param path Lokasi file untuk referensi kesalahan.
     * @param content Konten string yang akan diproses menjadi token.
     * @param location Lokasi saat ini dalam konten untuk pelacakan posisi.
     * @return Wrapper yang berisi daftar token yang dihasilkan.
     */
    static NToken::Wrapper tokenization(const std::string& path, std::string& content, NToken::Location& location);

    /**
     * @brief Menganalisis konten untuk menemukan dan membuat token.
     *
     * Fungsi ini mencari pola dalam konten menggunakan regex. Jika ditemukan,
     * akan membuat dan mengembalikan objek NToken. Jika tidak ada pola yang cocok,
     * proses akan berhenti.
     *
     * @param content Konten string yang akan dianalisis.
     * @param location Lokasi saat ini dalam konten untuk pelacakan posisi.
     * @return NToken yang dihasilkan dari analisis konten.
     */
    static NToken tokenAnalyzer(std::string& content, NToken::Location& location);

    /**
     * @brief Membuat objek NToken berdasarkan hasil pencocokan regex.
     *
     * Fungsi ini mengisi atribut dari objek NToken berdasarkan hasil pencocokan,
     * memperbarui lokasi saat ini dan menghapus bagian yang sudah diproses dari konten.
     *
     * @param match Hasil pencocokan regex dalam bentuk smatch.
     * @param content Konten string yang sedang diproses.
     * @param location Lokasi saat ini dalam konten untuk pelacakan posisi.
     * @param type Jenis NToken yang akan dibuat.
     * @return NToken yang telah dibuat dengan atribut lengkap.
     */
    static NToken tokenCreating(const std::smatch& match, std::string& content, NToken::Location& location, const NToken::Type& type);
};

} // namespace nlexer

#endif