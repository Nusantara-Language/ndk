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

void nusantara::PenganalisisSemantik::kunjungiTitikToken(const Titik& titik) {
  this->tempatNilaiSementara = titik.ambilToken().value().konten;
} // function kunjungiTitikToken

void nusantara::PenganalisisSemantik::kunjungiTitikAwal(const Titik& titik) {
  for(const auto& titikTurunan: titik.ambilKumpulanTitikTurunan()) {
    titikTurunan->terima(*this);
  }
} // function kunjungiTitikAwal 

void nusantara::PenganalisisSemantik::kunjungiTitikPernyataan(const Titik& titik) {
  for(const auto& titikTurunan: titik.ambilKumpulanTitikTurunan()) {
    titikTurunan->terima(*this);
  }
} // function kunjungiTitikPernyataan

void nusantara::PenganalisisSemantik::kunjungiTitikEkspresi(const Titik& titik) {
  titik.ambilKumpulanTitikTurunan()[0]->terima(*this);
  if(apaKahStringNumeric(std::get<std::string>(this->tempatNilaiSementara))) {
    this->tempatNilaiSementara = std::stoi(std::get<std::string>(this->tempatNilaiSementara));
  }
} // function kunjungiTitikEkspresi

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