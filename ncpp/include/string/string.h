/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef STRING_H
#define STRING_H

#include <string>
#include <string_view>
#include <vector>

namespace ncpp {

/**
 * @brief Menghapus whitespace dari awal dan akhir string.
 *
 * Fungsi ini memodifikasi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari awal dan akhir string. Jika
 * string hanya terdiri dari karakter whitespace, maka string akan dikosongkan.
 *
 * @param [in,out] str Referensi ke string yang akan dimodifikasi.
 * @return Referensi ke string yang telah dimodifikasi.
 *
 * @note Fungsi ini menggunakan metode `find_first_not_of` untuk menemukan posisi
 *       karakter pertama yang bukan whitespace dan `find_last_not_of` untuk menemukan
 *       posisi karakter terakhir yang bukan whitespace.
 *       Jika tidak ada karakter non-whitespace ditemukan, string akan dikosongkan.
 *       Fungsi ini tidak melempar pengecualian (ditandai dengan `noexcept`).
 */
std::string& trim(std::string& str) noexcept;

/**
 * @brief Menghapus whitespace dari awal string.
 *
 * Fungsi ini memodifikasi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari awal string. Jika string hanya
 * terdiri dari karakter whitespace, maka string akan dikosongkan.
 *
 * @param [in,out] str Referensi ke string yang akan dimodifikasi.
 * @return Referensi ke string yang telah dimodifikasi.
 *
 * @note Fungsi ini menggunakan metode `find_first_not_of` untuk menemukan posisi
 *       karakter pertama yang bukan whitespace. Jika tidak ada karakter non-whitespace
 *       ditemukan, string akan dikosongkan. Fungsi ini tidak melempar pengecualian
 *       (ditandai dengan `noexcept`).
 */
std::string& lTrim(std::string& str) noexcept;

/**
 * @brief Menghapus whitespace dari akhir string.
 *
 * Fungsi ini memodifikasi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari akhir string. Jika string hanya
 * terdiri dari karakter whitespace, maka string akan dikosongkan.
 *
 * @param [in,out] str Referensi ke string yang akan dimodifikasi.
 * @return Referensi ke string yang telah dimodifikasi.
 *
 * @note Fungsi ini menggunakan metode `find_last_not_of` untuk menemukan posisi
 *       karakter terakhir yang bukan whitespace. Jika tidak ada karakter non-whitespace
 *       ditemukan, string akan dikosongkan. Fungsi ini tidak melempar pengecualian 
 *       (ditandai dengan `noexcept`).
 */
std::string& rTrim(std::string& str) noexcept;

/**
 * @brief Menghapus whitespace dari awal dan akhir string.
 *
 * Fungsi ini mengonversi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari awal dan akhir string. Fungsi ini
 * memanggil fungsi `trim` untuk melakukan proses tersebut.
 *
 * @param str String yang akan dimodifikasi.
 * @return std::string Hasil string yang telah di-trim.
 *
 * @note Fungsi ini tidak memodifikasi string input secara langsung. Sebaliknya,
 *       fungsi ini mengembalikan salinan string yang telah dimodifikasi.
 */
std::string trimmed(std::string str) noexcept;

/**
 * @brief Menghapus whitespace dari awal string.
 *
 * Fungsi ini mengonversi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari awal string. Fungsi ini
 * memanggil fungsi `lTrim` untuk melakukan proses tersebut.
 *
 * @param str String yang akan dimodifikasi.
 * @return std::string Hasil string yang telah di-trim dari awal.
 *
 * @note Fungsi ini tidak memodifikasi string input secara langsung. Sebaliknya,
 *       fungsi ini mengembalikan salinan string yang telah dimodifikasi.
 */
std::string lTrimmed(std::string str) noexcept;

/**
 * @brief Menghapus whitespace dari akhir string.
 *
 * Fungsi ini mengonversi string input dengan menghapus semua karakter whitespace
 * (spasi, tab, newline, dan carriage return) dari akhir string. Fungsi ini
 * memanggil fungsi `rTrim` untuk melakukan proses tersebut.
 *
 * @param str String yang akan dimodifikasi.
 * @return std::string Hasil string yang telah di-trim dari akhir.
 *
 * @note Fungsi ini tidak memodifikasi string input secara langsung. Sebaliknya,
 *       fungsi ini mengembalikan salinan string yang telah dimodifikasi.
 */
std::string rTrimmed(std::string str) noexcept;

/**
 * @brief Memisahkan std::string_view menjadi potongan-potongan berdasarkan delimiter.
 *
 * Fungsi ini membagi string input menjadi beberapa potongan (token) berdasarkan
 * karakter delimiter yang diberikan. Hasilnya adalah vector yang berisi
 * potongan-potongan string. Jika opsi `keepEmpty` diatur ke true, potongan kosong
 * (yang dihasilkan dari delimiter berturut-turut) akan disertakan dalam hasil.
 *
 * @param str String yang akan dipisahkan.
 * @param delimiter Karakter yang digunakan sebagai pemisah.
 * @param keepEmpty Menentukan apakah potongan kosong harus disertakan dalam hasil.
 * @return std::vector<std::string_view> Vector yang berisi potongan-potongan string.
 *
 * @note Fungsi ini menggunakan metode `find` untuk menemukan posisi delimiter dan
 *       `substr` untuk mendapatkan token dari string. Fungsi ini tidak melempar
 *       pengecualian (ditandai dengan `noexcept`).
 */
std::vector<std::string_view> splitView(std::string_view str, char delimiter, bool keepEmpty = true) noexcept;

/**
 * @brief Memisahkan std::string menjadi potongan-potongan berdasarkan delimiter.
 *
 * Fungsi ini membagi string input menjadi beberapa potongan (token) berdasarkan
 * karakter delimiter yang diberikan. Hasilnya adalah vector yang berisi
 * potongan-potongan string. Jika opsi `keepEmpty` diatur ke true, potongan kosong
 * (yang dihasilkan dari delimiter berturut-turut) akan disertakan dalam hasil.
 *
 * @param str String yang akan dipisahkan.
 * @param delimiter Karakter yang digunakan sebagai pemisah.
 * @param keepEmpty Menentukan apakah potongan kosong harus disertakan dalam hasil.
 * @return std::vector<std::string> Vector yang berisi potongan-potongan string.
 *
 * @note Fungsi ini tidak melempar pengecualian (ditandai dengan `noexcept`).
 */
std::vector<std::string> split(const std::string& str, char delimiter, bool keepEmpty = true) noexcept;

/**
 * @brief Menggabungkan elemen-elemen dalam std::vector<std::string> menjadi satu string,
 *        dipisahkan oleh karakter delimiter.
 *
 * @param vec Vector string yang akan digabungkan.
 * @param delimiter Karakter yang digunakan sebagai pemisah antar elemen.
 * @return std::string Hasil gabungan dari elemen-elemen dalam vector.
 *
 * @note Fungsi ini menggunakan std::ostringstream untuk menggabungkan string dengan efisien.
 */
std::string join(const std::vector<std::string>& vec, char delimiter) noexcept;

/**
 * @brief Mengonversi std::vector<char> menjadi std::string.
 *
 * Fungsi ini mengubah elemen-elemen dalam vector karakter menjadi sebuah string.
 * Jika vector kosong, fungsi ini akan mengembalikan string kosong.
 *
 * @param vec Vector karakter yang akan dikonversi menjadi string.
 * @return std::string Hasil konversi dari vector ke string.
 *
 * @note Fungsi ini menggunakan konstruktor std::string yang menerima dua iterator
 *       (begin dan end) untuk membuat string dari elemen-elemen dalam vector.
 *       Fungsi ini tidak melempar pengecualian (ditandai dengan `noexcept`).
 */
std::string join(const std::vector<char>& vec) noexcept;

/**
 * @brief Mengnormalisasi sebuah string dengan mengubah newline character (\r) menjadi newline character (\n).
 *
 * @param [out] str Referensi string yang akan dimodifikasi.
 * @return Referensi string yang sama dengan masukan, namun telah dimodifikasi.
 */
std::string& normalize(std::string& str) noexcept;

/**
 * @brief Mengembalikan string yang telah dinormalisasi dengan mengganti karakter carriage return (\r)
 *        menjadi newline character (\n).
 *
 * @param str String yang akan dinormalisasi. Fungsi ini mengambil salinan dari string yang diberikan.
 * @return String yang telah dinormalisasi.
 *
 * @note Fungsi ini menggunakan fungsi `normalize` untuk melakukan proses normalisasi pada string.
 *       Setelah normalisasi, string yang telah dimodifikasi dikembalikan dengan menggunakan `std::move`,
 *       yang memungkinkan pengalihan kepemilikan data string tanpa melakukan salinan tambahan.
 */
std::string normalized(std::string str) noexcept;

bool isNumeric(std::string_view str);

bool isNumber(const std::string& str);

} // namespace ncpp

#endif