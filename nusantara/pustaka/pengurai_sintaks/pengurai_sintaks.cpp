/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <format>
#include <memory>
#include <string>
#include <vector>

#include "pengurai_sintaks/pengecualian_pengurai_sintaks.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"
#include "pendengar/a_pendengar_titik.hpp"
#include "token/tipe_token.hpp"

nusantara::PengecualianPenguraiSintaks nusantara::PenguraiSintaks::kesalahan(
  const nusantara::Token &token,
  const std::string &pesan
) {
  return PengecualianPenguraiSintaks(
    std::format(
    "Kesalahan sintaks pada {}:{}:{}\n -> {}",
      token.lokasiBerkas, 
      token.lokasi.baris,
      token.lokasi.kolom, 
      pesan
    )
  ); // constructor PengecualianPenguraiSintaks
} // function kesalahan

const nusantara::Token& nusantara::PenguraiSintaks::tokenSaatIni() const {
  return this->kumpulanToken[this->indeksTokenSaatIni];
} // fucntion tokenSaatIni

bool nusantara::PenguraiSintaks::apakahSudahDiAkhirFile() const {
  return this->tokenSaatIni().tipe == nusantara::TipeToken::akhirDariFile;
} // function apakahSudahDiAkhirFile

bool nusantara::PenguraiSintaks::cekTipeToken(const TipeToken &tipe) const {
  if (this->apakahSudahDiAkhirFile()) {
    return false;
  }
  return this->tokenSaatIni().tipe == tipe;
} // function cekTipeToken

const nusantara::Token& nusantara::PenguraiSintaks::tokenSebelumnya() {
  if (this->indeksTokenSaatIni == 0) {
    throw std::out_of_range("[PS] Berusaha mengakses token sebelum indeks awal.");
  }
  return this->kumpulanToken[this->indeksTokenSaatIni - 1];
} // function tokenSebelumnya

const nusantara::Token& nusantara::PenguraiSintaks::majuKeTokenSelanjutnya() {  
  if (!this->apakahSudahDiAkhirFile()) {
    this->indeksTokenSaatIni++;
  }
  return this->tokenSebelumnya();
} // function majuKeTokenSelanjutnya

const nusantara::Token& nusantara::PenguraiSintaks::makanToken(
  const nusantara::TipeToken &tipe,
  const std::string &pesanKesalahan
) {
  if (this->cekTipeToken(tipe)) {
    return this->majuKeTokenSelanjutnya();
  }
  throw PenguraiSintaks::kesalahan(this->tokenSaatIni(), pesanKesalahan);
} // function makanToken

bool nusantara::PenguraiSintaks::apakahTokenSaatIniAdalah(const std::vector<nusantara::TipeToken> &kumpulanTipeToken) {
  if(
    std::ranges::any_of(
      kumpulanTipeToken,
      [this](auto type) { return this->cekTipeToken(type); }
    ) // function any_of
  ) {
    this->majuKeTokenSelanjutnya();
    return true;
  } // if
  return false;
} // function apakahTokenSaatIniAdalah

void nusantara::PenguraiSintaks::uraikan() {
  auto titik = Titik{TipeTitik::AWAL};
  while (!this->apakahSudahDiAkhirFile()) {
    try {
      titik.tambahTitikTurunan(this->uraiPernyataanEkspresi());
    } catch (const PengecualianPenguraiSintaks &error) {
      std::cerr << error.what() << "\n\n";
      this->majuKeTokenSelanjutnya();
    } // catch
  } // while
  this->hasilPenguraian = std::make_unique<Titik>(std::move(titik));
} // function uraikan

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiPernyataanEkspresi() {
  auto titik = Titik{TipeTitik::PERNYATAAN_EKSPRESI};

  auto makanTokenTitikKoma = [this] -> const Token & {
    return this->makanToken(
      nusantara::TipeToken::titikKoma,
      "[PS] Jangan lupa titik koma."
    ); // fucntion makanToken
  }; // lambda makanTokenTitikKoma

  if(this->cekTipeToken(nusantara::TipeToken::identifikasi)) {
    titik.tambahTitikTurunan(this->uraiPanggilFungsi()); 
    if(this->psa) {
      makanTokenTitikKoma();
    }else{
      titik.tambahTitikTurunan(
        std::make_unique<Titik>(
          Titik{
            TipeTitik::TOKEN, 
            makanTokenTitikKoma()
          } // constructor Titik
        ) // constructor make_unique
      ); // function tambahTitikTurunan
    } // else
  }else{
    throw nusantara::PenguraiSintaks::kesalahan(this->tokenSaatIni(), "[PS] Pernyataan ekspresi tidak benar.");
  } // else

  return std::make_unique<Titik>(std::move(titik));
} // function uraiPernyataanEkspresi

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiPanggilFungsi() {
  auto titik = Titik{TipeTitik::PANGGIL_FUNGSI};

  titik.tambahTitikTurunan(
    std::make_unique<Titik>(
      Titik{
        TipeTitik::TOKEN, 
        this->makanToken(
          nusantara::TipeToken::identifikasi,
          "[PS] Nama fungsi belum ditentukan."
        ) // function makanToken
      } // constructor Titik
    ) // constructor make_unique
  ); // function tambahTitikTurunan

  titik.tambahTitikTurunan(this->uraiTempatParameterPanggilFungsi());

  return std::make_unique<Titik>(std::move(titik));
} // function uraiPanggilFungsi

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiTempatParameterPanggilFungsi() {
  auto titik = Titik{TipeTitik::TEMPAT_PARAMETER_PANGGIL_FUNGSI};

  auto makanTokenKurungBulatBuka = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatBuka,
      "[PS] Tempat parameter pada fungsi harus ada kurung bulat buka '('."
    ); // function makanToken
  }; // lambda makanTokenKurungBulatBuka

  auto makanTokenKurungBulatTutup = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatTutup,
      "[PS] Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
    ); // function makanToken
  }; // lambda makanTokenKurungBulatTutup

  if(this->psa) {
    makanTokenKurungBulatBuka();
    makanTokenKurungBulatTutup();
  }else{
    titik.tambahTitikTurunan(
      std::make_unique<Titik>(
        Titik{
          TipeTitik::TOKEN,
          makanTokenKurungBulatBuka()
        } // constructor Titik
      ) // constructor make_unique
    ); // function tambahTitikTurunan

    titik.tambahTitikTurunan(
      std::make_unique<Titik>(
        Titik{
          TipeTitik::TOKEN,
          makanTokenKurungBulatTutup()
        } // constructor Titik
      ) // constructor make_unique
    ); // function tambahTitikTurunan
  } // else

  return std::make_unique<Titik>(std::move(titik));
} // function uraiTempatParameterPanggilFungsi

void nusantara::PenguraiSintaks::cetak() {
  if(this->hasilPenguraian != nullptr) {
    cetakTitik(*this->hasilPenguraian, 0);
  }
} // function cetak

const std::unique_ptr<nusantara::Titik>& nusantara::PenguraiSintaks::ambilHasil() const {
  return this->hasilPenguraian;
} // function ambilHasil

void nusantara::PenguraiSintaks::aturKumpulanToken(const std::vector<nusantara::Token>& kumpulanToken) {
  this->kumpulanToken = kumpulanToken;
} // function aturKumpulanToken