/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <format>
#include <iostream>

#include "error/file_content_exception.h"
#include "file/file_txt.h"
#include "nlexer.h"
#include "ntoken.h"


namespace nlexer {

/**
 * @brief Konstruktor untuk kelas NLexer.
 *
 * Menerima shared pointer ke vector yang berisi Wrapper token.
 *
 * @param twraps Shared pointer ke vector yang menyimpan Wrapper token.
 */
NLexer::NLexer(const std::shared_ptr<std::vector<NToken::Wrapper>>& twraps) : twraps(twraps) {}

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
NToken::Wrapper& NLexer::input(const std::string& input, const std::string& path)
{
    std::string content = input;                                   // Menyimpan konten input
    NToken::Location location{1, 1};                               // Inisialisasi lokasi token
    NToken::Wrapper tWrap = tokenization(path, content, location); // Tokenisasi konten

    this->twraps->emplace_back(tWrap); // Menambahkan Wrapper token ke vector
    return this->twraps->back();       // Mengembalikan referensi ke Wrapper terakhir
}

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
NToken::Wrapper& NLexer::inputFile(const std::string& path)
{
    ncpp::FileTxt file(path);                                                          // Membuat objek FileTxt untuk membaca file
    if (!file.exist())                                                                 // Memeriksa keberadaan file
        throw std::runtime_error(std::format("File '{}' tidak ada.", file.getPath())); // Melempar pengecualian jika tidak ada

    file.read();                                         // Membaca konten file
    return this->input(file.getEditableContent(), path); // Memproses konten dan mengembalikan Wrapper token
}

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
NToken::Wrapper NLexer::tokenization(const std::string& path, std::string& content, NToken::Location& location)
{
    std::vector<NToken> tokens; // Daftar untuk menyimpan token yang dihasilkan

    while (content.size() > 0) // Selama ada konten yang tersisa
    {
        auto token = tokenAnalyzer(content, location); // Menganalisis konten untuk menghasilkan token

        if (token.type == NToken::UNKNOWN) // Jika token tidak dikenali
        {
            std::cerr << ncpp::FileContentException(ncpp::FileContentException::Type::ERROR, "Bagian ini tidak dapat dikenali.", path, token.content, token.location.row, token.location.column);
        }

        tokens.emplace_back(std::move(token)); // Menambahkan token ke daftar
    }

    if (tokens.back().type != NToken::NEOF)
    {
        tokens.emplace_back(NToken{location, "", NToken::NEOF}); // Menambahkan token EOF
    }

    return {path, tokens}; // Mengembalikan Wrapper dengan daftar token
}

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
NToken NLexer::tokenAnalyzer(std::string& content, NToken::Location& location)
{
    NToken result;     // Token hasil analisis
    std::smatch match; // Variabel untuk menyimpan hasil pencocokan regex

    while (true)
    {
        bool foundToken = false; // Flag untuk menandai jika token ditemukan

        for (const NToken::Data& data : nlexer::tokenData) // Iterasi melalui data token
        {
            if (std::regex_search(content, match, data.pattern)) // Mencari pola regex dalam konten
            {
                result = tokenCreating(match, content, location, data.type); // Membuat token dari hasil pencocokan

                foundToken = true; // Token ditemukan

                if (data.type == NToken::Type::NEWLINE) // Jika jenisnya adalah NEWLINE
                {
                    location.row++;      // Menaikkan nomor baris
                    location.column = 1; // Reset kolom ke 1
                }

                if (!data.skip) // Jika tidak perlu melewati
                {
                    return result; // Kembalikan hasil token
                }

                break; // Keluar dari loop for jika sudah menemukan satu kecocokan
            }
        }

        if (!foundToken)
        {          // Jika tidak ada kecocokan ditemukan
            break; // Keluar dari loop while
        }
    }

    return {location, "", NToken::NEOF};
}

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
NToken NLexer::tokenCreating(const std::smatch& match, std::string& content, NToken::Location& location, const NToken::Type& type)
{
    NToken token;                // Objek NToken baru
    token.content = match.str(); // Mengisi konten dengan hasil pencocokan
    token.location = location;   // Mengisi lokasi dengan lokasi saat ini
    token.type = type;           // Mengisi jenis dengan tipe yang diberikan

    location.column += match.str().length();         // Memperbarui kolom berdasarkan panjang hasil pencocokan
    content.erase(match.position(), match.length()); // Menghapus bagian yang sudah diproses dari konten

    return token; // Kembalikan objek NToken yang telah dibuat
}

} // namespace nlexer