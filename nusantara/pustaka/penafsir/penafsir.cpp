/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <any>
#include <string>

#include "penafsir/penafsir.hpp"
#include "cetak/cetak.hpp"

void nusantara::Penafsir::kunjungiTitikToken(const Titik& titik) {
  // Atur data sementara di runtime untuk menyimpan nama fungsi.
  if(titik.ambilToken()) this->lingkunganEksekusi.aturDataSementara(titik.ambilToken()->konten);
} // function kunjungiTitikToken

void nusantara::Penafsir::kunjungiTitikPanggilFungsi(const nusantara::Titik& node) {
  // Pergi ke child index ke-0 untuk mendapatkan nama fungsi
  node.ambilKumpulanTitikTurunan()[0]->terima(*this);

  // Panggil fungsi sesuai nama
  this->lingkunganEksekusi.ambilBlokKode()
    .ambilKumpulanFungsi()
    .panggilFungsi(
      std::any_cast<std::string>(
        this->lingkunganEksekusi.ambilDataSementara()
      )
    );
} // function kunjungiTitikPanggilFungsi

void nusantara::Penafsir::kunjungiTitikAwal(const nusantara::Titik& titik) {
  for (const auto& child : titik.ambilKumpulanTitikTurunan()) {
    child->terima(*this);
  }
} // function kunjungiTitikAwalNode

void nusantara::Penafsir::kunjungiTitikPernyataanEkspresi(const nusantara::Titik& titik) {
  if(titik.ambilKumpulanTitikTurunan().size() > 0) titik.ambilKumpulanTitikTurunan()[0]->terima(*this);
} // function kunjungiTitikPernyataanEkspresiNode

void nusantara::Penafsir::kunjungiTitikTempatParameterPanggilFungsi(const nusantara::Titik&) {
  // Tidak mengeksekusi apa apa
} // function kunjungiTitikTempatParameterPanggilFungsi

void nusantara::Penafsir::kunjungiTitikAkhirDariFile(const nusantara::Titik& titik) {
  // Tidak mengeksekusi apa apa
} // function kunjungiTitikAkhirDariFile

void nusantara::Penafsir::kunjungiTitikBilangan(const nusantara::Titik& titik) {
  // Karena belum ada kode untuk mengelolah ekspresi bilangan, cetak aja langsung ke konsol
  cetakDBB(titik.ambilKumpulanTitikTurunan()[0]->ambilToken().value().konten);
} // function kunjungiTitikBilangan
