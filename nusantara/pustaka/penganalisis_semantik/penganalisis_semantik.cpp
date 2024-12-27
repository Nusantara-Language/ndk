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
#include "alat.hpp"
#include "konfig/konfig_label_keluaran.hpp"
#include "pengurai_sintaks/titik/titik.hpp"
#include "cetak/cetak.hpp"

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
      __NK__LABEL_KELUARAN_AS__ "fungsi '" + namaFungsiToken.konten + "' belum dibuat."
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
    nusantara::cetak(this->pengecualianSintaks.what());
    exit(0);
  } // if
} // function kunjungiTitikAkhirDariFile

void nusantara::PenganalisisSemantik::kunjungiTitikBilangan(const Titik& titik) {
  const Token& tokenBilangan = titik.ambilKumpulanTitikTurunan()[0]->ambilToken().value();
  if(!apaKahStringNumeric(tokenBilangan.konten)) {
    this->pengecualianSintaks.tambahData({
      tokenBilangan.lokasiBerkas,
      tokenBilangan.lokasi,
      tokenBilangan.konten,
      __NK__LABEL_KELUARAN_AS__ "Bukan lah sebuah bilangan."
    }); // function tambahData
  } // if
} // function kunjungiTitikBilangan