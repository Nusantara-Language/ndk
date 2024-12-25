/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "lingkungan_eksekusi/kawasan/kawasan.hpp"
#include "lingkungan_eksekusi/fungsi/fungsi.hpp"

nusantara::Fungsi::Fungsi(
  const std::string& nama
): nama(nama), kawasan({}, {}) {}

nusantara::Fungsi::Fungsi(
  const std::string& nama, 
  Kawasan&& kawasan
): nama(nama), kawasan(std::move(kawasan)) {}

void nusantara::Fungsi::panggil() {
  this->kawasan.ambilKumpulanIntruksi().jalankan();
} // function panggil

const std::string& nusantara::Fungsi::ambilNama() {
  return this->nama;
}  // function ambilNama