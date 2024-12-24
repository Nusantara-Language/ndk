/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */


#include <functional>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <format>
#include <string>
#include <vector>
#include <regex>

#include "perintah/perintah.hpp"
#include "cetak/cetak.hpp"


/**
 * @brief Konstruktor untuk membuat objek Perintah.
 *
 * @param nama Nama perintah yang akan digunakan.
 * @param deskripsi Deskripsi singkat tentang apa yang dapat dilakukan dengan perintah ini.
 * @param intruksi Fungsi yang akan dijalankan ketika perintah diterjemahkan ke dalam kode eksekusi.
 * @param tanpaArgumen Boolean yang menentukan apakah perintah dapat digunakan tanpa argumen.
 */
nusantara::Perintah::Perintah(
  std::string nama,
  std::string deskripsi,
  std::function<void(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &kumpulanArgumen)> intruksi,
  const bool &tanpaArgumen
): Perintah(
  std::regex(nama), // Membuat regex untuk nama perintah yang akan digunakan.
  std::move(nama), // Mempindahkan nama perintah ke konstruktor.
  std::move(deskripsi), // Mempindahkan deskripsi perintah ke konstruktor.
  std::move(intruksi), // Mempindahkan fungsi intruksi ke konstruktor.
  tanpaArgumen // Menentukan apakah perintah dapat digunakan tanpa argumen.
) {}

/**
 * @brief Konstruktor alternatif untuk membuat objek Perintah.
 *
 * @param regex Regex yang akan digunakan sebagai nama perintah.
 * @param nama Nama perintah yang akan digunakan.
 * @param deskripsi Deskripsi singkat tentang apa yang dapat dilakukan dengan perintah ini.
 * @param intruksi Fungsi yang akan dijalankan ketika perintah diterjemahkan ke dalam kode eksekusi.
 * @param tanpaArgumen Boolean yang menentukan apakah perintah dapat digunakan tanpa argumen.
 */
nusantara::Perintah::Perintah(
  std::regex regex,
  std::string nama,
  std::string deskripsi,
  std::function<void(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &kumpulanArgumen)> intruksi,
  const bool &tanpaArgumen
):
  regex(std::move(regex)), // Membuat regex untuk nama perintah yang akan digunakan.
  nama(std::move(nama)), // Mempindahkan nama perintah ke konstruktor.
  deskripsi(std::move(deskripsi)), // Mempindahkan deskripsi perintah ke konstruktor.
  intruksi(std::move(intruksi)), // Mempindahkan fungsi intruksi ke konstruktor.
  tanpaArgumen(tanpaArgumen) // Menentukan apakah perintah dapat digunakan tanpa argumen.
{
    // Konstruktor alternatif dengan sintaks yang lebih singkat dan efisien.
    // Dengan menggunakan std::move, kita dapat memindahkan nilai-nilai secara langsung ke konstruktor,
    // sehingga mengurangi biaya operasi dan meningkatkan kinerja program.
}

/**
 * @brief Mendapatkan nama perintah.
 *
 * @return Reference string untuk nama perintah.
 */
const std::string& nusantara::Perintah::ambilNama() const {
  return this->nama;
}

/**
 * @brief Mendapatkan deskripsi perintah.
 *
 * @return Reference string untuk deskripsi perintah.
 */
const std::string& nusantara::Perintah::ambilDeskripsi() const {
  return this->deskripsi;
}

/**
 * @brief Mendapatkan regex nama perintah.
 *
 * @return Reference regex untuk nama perintah.
 */
const std::regex& nusantara::Perintah::ambilRegex() const {
  return this->regex;
}

/**
 * @brief Mengubah perintah ke string yang dapat dibaca.
 *
 * @return String yang mengandung nama dan deskripsi perintah.
 */
std::string nusantara::Perintah::ubahKeString() const  {
  return std::format(
    "{} - {}",
    this->nama,
    this->deskripsi
  );
}

/**
 * @brief Mengjalankan perintah secara langsung.
 *
 * @param eksekusiPerintah Objek yang akan dijalankan sebagai perintah.
 * @param indeksSaatIni Indeks saat ini dalam eksekusi perintah.
 * @param kumpulanArgumen Kumpulan argumen yang digunakan saat perintah dijalankan.
 */
void nusantara::Perintah::eksekusi(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &argumen) {
  // Periksa jika perintah tidak memerlukan argumen dan jumlah argumen yang digunakan lebih dari 2.
  if(this->tanpaArgumen && argumen.size() > 2) {
    // Jika condition true, tampilkan pesan error menggunakan fungsi std::cetakDF.
    nstd::cetakDF("Perintah {} tidak memerlukan argumen.", this->nama);
    return;
  }
  // Jika condisional false, jalankan fungsi intruksi dengan argument yang sesuai.
  this->intruksi(eksekusiPerintah, indeksSaatIni, argumen);
}

/**
 * @brief Mengoperasikan perintah secara langsung.
 *
 * @param lain Objek Perintah lain yang akan dioperasikan.
 *
 * @return Boolean yang menentukan apakah perintah dapat dioperasikan dengan sama (true) atau tidak (false).
 */
bool nusantara::Perintah::operator==(const Perintah& lain) {
  // Periksa jika nama dan deskripsi perintah sama.
  return this->nama == lain.nama || this->deskripsi == lain.deskripsi;
}

/**
 * @brief Menambahkan perintah baru ke dalam kumpulan perintah.
 *
 * @param perintah Objek Perintah yang akan ditambahkan.
 */
void nusantara::EksekusiPerintah::tambah(Perintah perintah) {
  // Periksa jika perintah belum ada di dalam kumpulan perintah.
  if(std::find(this->kumpulanPerintah.begin(), this->kumpulanPerintah.end(), perintah) == this->kumpulanPerintah.end()) {
    // Jika condition true, tambahkan perintah baru ke dalam kumpulan perintah.
    this->kumpulanPerintah.push_back(std::move(perintah));
  }
}

/**
 * @brief Mengambil kumpulan perintah yang ada di dalam objek EksekusiPerintah.
 *
 * @return Reference vector untuk kumpulan perintah.
 */
const std::vector<nusantara::Perintah>& nusantara::EksekusiPerintah::ambilKumpulanPerintah() {
  return this->kumpulanPerintah;
}

/**
 * @brief Menjalankan perintah secara langsung.
 *
 * Fungsi ini digunakan untuk menjalankan perintah yang ada di dalam kumpulan perintah.
 *
 * @param argumen Vektor string yang mengandung argumen perintah.
 */
void nusantara::EksekusiPerintah::eksekusi(std::vector<std::string> argumen) {
  // Initialize variabel currentIndex ke 1.
  size_t currentIndex = 1;

  // Jika jumlah argumen hanya 1, maka jalankan perintah pertama di kumpulan perintah.
  if (argumen.size() == 1) {
    this->kumpulanPerintah[0].eksekusi(*this, currentIndex, argumen);
    return;
  }
  
  // Loop through kumpulan perintah.
  for (auto& perintah : this->kumpulanPerintah) {
    // Jika pattern argumen[currentIndex] cocok dengan regex nama perintah, maka jalankan perintah tersebut.
    if (std::regex_match(argumen[currentIndex], perintah.ambilRegex())) {
      perintah.eksekusi(*this, currentIndex, argumen);
      // Increment currentIndex untuk mencari perintah selanjutnya.
      currentIndex++;
      return;
    }
  }
}