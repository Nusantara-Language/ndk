/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <memory>
#include <string>

#include "penganalisis_semantik/penganalisis_semantik.hpp"
#include "cetak/cetak.hpp"
#include "pengurai_sintaks/titik/titik.hpp"

void nusantara::PenganalisisSemantik::kunjungiTitikToken(const Titik&) {
  // Tidak melakukan apa-apa
} // function kunjungiTitikToken

void nusantara::PenganalisisSemantik::kunjungiTitikPanggilFungsi(const Titik& titik) {
  const Token& namaFungsiToken = titik.ambilKumpulanTitikTurunan()[0]->ambilToken().value();
  if (namaFungsiToken.konten != "halodunia") {
    this->pengecualianSintaks.tambahData({
      namaFungsiToken.lokasiBerkas,
      namaFungsiToken.lokasi,
      namaFungsiToken.konten,
      "[AS] fungsi '" + namaFungsiToken.konten + "' belum dibuat."
    }); // function tambahData
  } // if
} // function kunjungiTitikPanggilFungsi

void nusantara::PenganalisisSemantik::kunjungiTitikAwal(const Titik& titik) {
  for(const auto& titikTurunan: titik.ambilKumpulanTitikTurunan()) {
    titikTurunan->terima(*this);
  }
} // function kunjungiTitikAwal 

void nusantara::PenganalisisSemantik::kunjungiTitikPernyataanEkspresi(const Titik& titik) {
  for(const auto& titikTurunan: titik.ambilKumpulanTitikTurunan()) {
    titikTurunan->terima(*this);
  }
} // function kunjungiTitikPernyataanEkspresi

void nusantara::PenganalisisSemantik::kunjungiTitikTempatParameterPanggilFungsi(const Titik&) {
  // Tidak melakukan apa-apa
} // function kunjungiTitikTempatParameterPanggilFungsi

void nusantara::PenganalisisSemantik::kunjungiTitikAkhirDariFile(const Titik& titik) {;
  if(this->pengecualianSintaks.apaKahAdaData()) {
    this->pengecualianSintaks.perbaruiPesanSesuaiData();
    nstd::cetak(this->pengecualianSintaks.what());
    exit(0);
  } // if
} // function kunjungiTitikAkhirDariFile