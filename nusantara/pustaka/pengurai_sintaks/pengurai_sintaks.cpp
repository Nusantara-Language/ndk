/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include <cstdlib>
#include <utility>
#include <memory>
#include <string>
#include <vector>

#include "cetak/cetak.hpp"
#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"
#include "pendengar/a_pendengar_titik.hpp"
#include "token/tipe_token.hpp"

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
    return this->kumpulanToken[0];
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
  throw DataPengecualianSintaks{
    .lokasiBerkas=this->tokenSaatIni().lokasiBerkas,
    .lokasiToken=this->tokenSaatIni().lokasi,
    .konten=this->tokenSaatIni().konten,
    .pesan=pesanKesalahan
  };
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
    } catch (const DataPengecualianSintaks &data) {
      this->pengecualianSintaks.tambahData(data);
      this->majuKeTokenSelanjutnya();
    } // catch
  } // while

  try {
    titik.tambahTitikTurunan(this->uraiAkhirDariFile());
  } catch (const DataPengecualianSintaks &data) {
    this->pengecualianSintaks.tambahData(data);
  } // catch

  if(this->pengecualianSintaks.apaKahAdaData()) {
    this->pengecualianSintaks.perbaruiPesanSesuaiData();
    nstd::cetak(this->pengecualianSintaks.what());
    exit(1);
  }

  this->hasilPenguraian = std::make_unique<Titik>(std::move(titik));
} // function uraikan

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiPernyataanEkspresi() {
  auto titik = Titik{TipeTitik::PERNYATAAN_EKSPRESI};

  auto makanTokenTitikKoma = [this] -> const Token & {
    return this->makanToken(
      nusantara::TipeToken::titikKoma,
      "[PENGURAI SINTAKS] Jangan lupa titik koma."
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
  }

  // Jika hanya ada 1 titik turunan saja itu yang akan di keluarkan.
  if(titik.ambilKumpulanTitikTurunan().size() == 1 && this->psa) {
    return titik.keluarKanTitikTurunan(0);
  }

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
          "[PENGURAI SINTAKS] Nama fungsi belum dibuat."
        ) // function makanToken
      } // constructor Titik
    ) // constructor make_unique
  ); // function tambahTitikTurunan

  auto titikTempatParameterPanggilFungsi = this->uraiTempatParameterPanggilFungsi();
  if(titikTempatParameterPanggilFungsi != nullptr && titikTempatParameterPanggilFungsi->ambilKumpulanTitikTurunan().size() > 0) {
    titik.tambahTitikTurunan(std::move(titikTempatParameterPanggilFungsi));
  } // if

  return std::make_unique<Titik>(std::move(titik));
} // function uraiPanggilFungsi

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiTempatParameterPanggilFungsi() {
  auto titik = Titik{TipeTitik::TEMPAT_PARAMETER_PANGGIL_FUNGSI};

  auto makanTokenKurungBulatBuka = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatBuka,
      "[PENGURAI SINTAKS] Tempat parameter pada fungsi harus ada kurung bulat buka '('."
    ); // function makanToken
  }; // lambda makanTokenKurungBulatBuka

  auto makanTokenKurungBulatTutup = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatTutup,
      "[PENGURAI SINTAKS] Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
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

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiAkhirDariFile() {
  auto titik = Titik{TipeTitik::AKHIR_DARI_FILE};
  if(this->apakahSudahDiAkhirFile()) {
    if(!this->psa) {
      titik.tambahTitikTurunan(
          std::make_unique<Titik>(
            Titik{
              TipeTitik::TOKEN,
              this->tokenSaatIni()
            } // constructor Titik
          ) // constructor make_unique
        ); // function tambahTitikTurunan
    } // if
  }else{
    throw DataPengecualianSintaks{
      .lokasiBerkas=this->tokenSaatIni().lokasiBerkas,
      .lokasiToken=this->tokenSaatIni().lokasi,
      .konten=this->tokenSaatIni().konten,
      .pesan="[PENGURAI SINTAKS] harus nya akhir dari file."
    }; // throw
  } // else
  return std::make_unique<Titik>(std::move(titik));
} // fungsi uraiAkhirDariFile

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