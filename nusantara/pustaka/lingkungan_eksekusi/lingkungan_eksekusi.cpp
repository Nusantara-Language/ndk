/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <utility>
#include <memory>
#include <any>

#include "lingkungan_eksekusi/lingkungan_eksekusi.hpp"
#include "lingkungan_eksekusi/fungsi/kumpulan_fungsi/fungsi_halodunia.hpp"
#include "lingkungan_eksekusi/kawasan/kawasan.hpp"

nusantara::LingkunganEksekusi::LingkunganEksekusi(): kawasan({}, {}) {
  // Inisialisasi
  this->kawasan.ambilKumpulanFungsi().tambahFungsi(std::move(std::make_unique<FungsiHaloDunia>()));
} // constructor kawasan

nusantara::Kawasan& nusantara::LingkunganEksekusi::ambilKawasan() {
  return this->kawasan;
} // function ambilKawasan

std::any nusantara::LingkunganEksekusi::ambilDataSementara() {
  return this->dataSementara;
} // function ambilDataSementara

void nusantara::LingkunganEksekusi::aturDataSementara(std::any nilai) {
  this->dataSementara = std::move(nilai);
} // function aturDataSementara 

void nusantara::LingkunganEksekusi::hapusDataSementara() {
  this->dataSementara.reset();
} // function hapusDataSementara
