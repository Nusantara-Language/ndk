/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NNMAP_H
#define NNMAP_H

#include <string>
#include <vector>

namespace ncpp {

/**
 * @brief Memetakan file ke dalam memori dan mengembalikan isinya sebagai std::vector<char>.
 *
 * Fungsi ini membuka file yang ditentukan, memetakannya ke dalam memori,
 * dan mengembalikan konten file sebagai vector karakter. Fungsi ini
 * mendukung platform Windows dan Unix-like (Linux/MacOS).
 *
 * @param filename Nama file yang akan dipetakan.
 * @return std::vector<char> Vector yang berisi konten file.
 *
 * @throws std::runtime_error Jika terjadi kesalahan saat membuka file,
 *         mendapatkan ukuran file, atau memetakan file ke dalam memori.
 *
 * @note
 * - Pada Windows, fungsi ini menggunakan API Windows untuk membuka file,
 *   membuat pemetaan file, dan memetakan tampilan file.
 * - Pada Linux/MacOS, fungsi ini menggunakan sistem panggilan POSIX untuk
 *   membuka file, mendapatkan ukuran file dengan lseek, dan memetakan
 *   file menggunakan mmap.
 */
std::vector<char> nnmap(const std::string& filename);

} // namespace ncpp

#endif