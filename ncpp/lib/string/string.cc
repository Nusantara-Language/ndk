/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "string/string.h"
#include <cctype>
#include <sstream>
#include <string>
#include <string_view>

namespace ncpp {

// Konstanta yang berisi karakter whitespace yang akan dihapus.
static const std::string WHITESPACE = " \t\n\r";

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
std::string& trim(std::string& str) noexcept
{
    // Jika string kosong, kembalikan string kosong.
    if (str.empty())
        return str;

    // Temukan posisi whitespace pertama yang bukan whitespace
    size_t start = str.find_first_not_of(WHITESPACE);
    // Temukan posisi whitespace terakhir yang bukan whitespace
    size_t end = str.find_last_not_of(WHITESPACE);

    // Jika tidak ada karakter non-whitespace ditemukan,
    // maka semua karakter adalah whitespace.
    if (start == std::string::npos)
    {
        str.clear(); // Semua karakter adalah whitespace
    }
    else
    {
        // Menggunakan erase untuk memangkas tanpa membuat salinan baru
        str.erase(0, start);        // Menghapus karakter sebelum posisi start
        str.erase(end - start + 1); // Menghapus karakter setelah end
    }

    return str; // Mengembalikan referensi ke string yang telah dimodifikasi
}

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
std::string& lTrim(std::string& str) noexcept
{
    // Jika string kosong, kembalikan string kosong.
    if (str.empty())
        return str;

    // Temukan posisi whitespace pertama yang bukan whitespace
    size_t start = str.find_first_not_of(WHITESPACE);

    // Jika tidak ada karakter non-whitespace ditemukan,
    // maka semua karakter adalah whitespace.
    if (start == std::string::npos)
    {
        str.clear(); // Mengosongkan string jika hanya terdapat whitespace
    }
    else
    {
        // Hapus semua karakter sebelum posisi start
        str.erase(0, start); // Menghapus karakter dari awal hingga posisi start
    }

    return str; // Mengembalikan referensi ke string yang telah dimodifikasi
}

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
std::string& rTrim(std::string& str) noexcept
{
    // Jika string kosong, kembalikan string kosong.
    if (str.empty())
        return str;

    // Temukan posisi whitespace terakhir yang bukan whitespace
    size_t end = str.find_last_not_of(WHITESPACE);

    // Jika tidak ada karakter non-whitespace ditemukan,
    // maka semua karakter adalah whitespace.
    if (end == std::string::npos)
    {
        str.clear(); // Mengosongkan string jika hanya terdapat whitespace
    }
    else
    {
        // Hapus semua karakter setelah posisi end
        str.erase(end + 1); // Menghapus karakter setelah posisi end
    }

    return str; // Mengembalikan referensi ke string yang telah dimodifikasi
}

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
std::string trimmed(std::string str) noexcept
{
    return trim(str);
}

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
std::string lTrimmed(std::string str) noexcept
{
    return lTrim(str);
}

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
std::string rTrimmed(std::string str) noexcept
{
    return rTrim(str);
}

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
std::vector<std::string_view> splitView(std::string_view str, char delimiter, bool keepEmpty) noexcept
{
    std::vector<std::string_view> result; // Vector untuk menyimpan hasil pemisahan
    size_t start = 0;                     // Posisi awal untuk mencari token

    while (start < str.size())
    {
        // Mencari posisi delimiter berikutnya
        size_t end = str.find(delimiter, start);
        // Mendapatkan substring dari posisi start hingga end
        auto token = str.substr(start, end - start);

        // Menambahkan token ke hasil jika tidak kosong atau jika keepEmpty true
        if (keepEmpty || !token.empty())
        {
            result.emplace_back(token);
        }

        // Jika tidak ada lagi delimiter, keluar dari loop
        if (end == std::string_view::npos)
            break;

        // Memperbarui posisi start untuk mencari token berikutnya
        start = end + 1;
    }

    // Menangani kasus di mana ada delimiter di akhir string
    if (keepEmpty && start == str.size())
    {
        result.emplace_back(""); // Tambahkan token kosong jika keepEmpty true
    }

    return result; // Mengembalikan vector hasil pemisahan
}

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
std::vector<std::string> split(const std::string& str, char delimiter, bool keepEmpty) noexcept
{
    std::vector<std::string> result; // Vector untuk menyimpan hasil pemisahan
    size_t start = 0;                // Posisi awal untuk mencari token

    while (start < str.size())
    {
        // Mencari posisi delimiter berikutnya
        size_t end = str.find(delimiter, start);
        // Mendapatkan substring dari posisi start hingga end
        auto token = str.substr(start, end - start);

        // Menambahkan token ke hasil jika tidak kosong atau jika keepEmpty true
        if (keepEmpty || !token.empty())
        {
            result.emplace_back(token);
        }

        // Jika tidak ada lagi delimiter, keluar dari loop
        if (end == std::string::npos)
            break;

        // Memperbarui posisi start untuk mencari token berikutnya
        start = end + 1;
    }

    // Menangani kasus di mana ada delimiter di akhir string
    if (keepEmpty && start == str.size())
    {
        result.emplace_back(""); // Tambahkan token kosong jika keepEmpty true
    }

    return result; // Mengembalikan vector hasil pemisahan
}

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
std::string join(const std::vector<std::string>& vec, char delimiter) noexcept
{
    // Jika vector kosong, kembalikan string kosong.
    if (vec.empty())
        return "";

    // Membuat objek ostringstream untuk membangun string hasil gabungan.
    std::ostringstream result;

    // Loop melalui setiap elemen dalam vector.
    for (size_t i = 0; i < vec.size(); ++i)
    {
        // Menambahkan elemen saat ini ke hasil gabungan.
        result << vec[i];

        // Jika bukan elemen terakhir, tambahkan delimiter setelah elemen.
        if (i != vec.size() - 1)
        {
            result << delimiter;
        }
    }

    // Mengembalikan hasil gabungan sebagai string.
    return result.str();
}

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
std::string join(const std::vector<char>& vec) noexcept
{
    // Jika vector kosong, kembalikan string kosong.
    if (vec.empty())
        return {};

    // Menggunakan konstruktor std::string untuk membuat string dari iterator.
    return {vec.begin(), vec.end()};
}

/**
 * @brief Mengnormalisasi sebuah string dengan mengubah newline character (\r) menjadi newline character (\n).
 *
 * @param [out] str Referensi string yang akan dimodifikasi.
 * @return Referensi string yang sama dengan masukan, namun telah dimodifikasi.
 */
std::string& normalize(std::string& str) noexcept
{
    /**
     * Jika string referensi kosong, maka fungsi akan langsung mengeluarkannya sebagai string kosong.
     */
    if (str.empty())
        return str;

    /**
     * Variabel index pembaca (`readIndex`) digunakan untuk melacak posisi saat ini dalam string,
     * sedangkan variabel index penulisan (`writeIndex`) digunakan untuk menyimpan posisi tempat data akan ditulis.
     */
    size_t writeIndex = 0;

    /**
     * Loop melalui seluruh isi string menggunakan loop For-Each.
     */
    for (size_t readIndex = 0; readIndex < str.size(); ++readIndex)
    {
        /**
         * Cek apabila karakter saat ini adalah carriage return ('\r').
         */
        if (str[readIndex] == '\r')
        {
            /**
             * Apabila \r diikuti oleh newline character ('\n'), maka \r dapat dilewatkan.
             */
            if (readIndex + 1 < str.size() && str[readIndex + 1] == '\n')
            {
                continue; // Lewati \r karena diikuti oleh \n
            }

            /**
             * Ganti \r dengan \n.
             */
            str[writeIndex++] = '\n';
        }
        else
        {
            /**
             * Untuk karakter lain, salinlah ke lokasi penulisan.
             */
            str[writeIndex++] = str[readIndex];
        }
    }

    /**
     * Setelah proses normalisasi selesai, resize string untuk mengatur ulang kapasitasnya sesuai dengan panjang yang baru.
     */
    str.resize(writeIndex);

    return str;
}

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
std::string normalized(std::string str) noexcept
{
    // Memanggil fungsi normalize untuk memodifikasi string input.
    normalize(str);

    // Mengembalikan string yang telah dinormalisasi dengan memindahkan kepemilikan.
    return std::move(str);
}

bool isNumeric(std::string_view str)
{
    for (char c : str)
    {
        if (std::isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
}

bool isNumber(const std::string& str)
{
    std::istringstream iss(str);
    double num;
    char c;
    return (iss >> num) && !(iss >> c);
}

} // namespace ncpp