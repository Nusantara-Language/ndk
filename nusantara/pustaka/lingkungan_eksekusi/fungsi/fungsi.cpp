/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "lingkungan_eksekusi/blok_kode/blok_kode.hpp"
#include "lingkungan_eksekusi/fungsi/fungsi.hpp"

nusantara::Fungsi::Fungsi(
  const std::string& nama
): nama(nama), blokKode({}, {}) {}

nusantara::Fungsi::Fungsi(
  const std::string& nama, 
  BlokKode&& blokKode
): nama(nama), blokKode(std::move(blokKode)) {}

void nusantara::Fungsi::panggil() {
  this->blokKode.ambilKumpulanIntruksi().jalankan();
} // function panggil

const std::string& nusantara::Fungsi::ambilNama() {
  return this->nama;
}  // function ambilNama