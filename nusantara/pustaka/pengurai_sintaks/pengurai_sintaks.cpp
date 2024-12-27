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
#include "konfig/konfig_label_keluaran.hpp"
#include "konfig/konfig_sintaks.hpp"
#include "pengurai_sintaks/titik/tipe_titik.hpp"
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

bool nusantara::PenguraiSintaks::cekTipeToken(const std::vector<nusantara::TipeToken> &kumpulanTipeToken) const {
  if(
    std::ranges::any_of(
      kumpulanTipeToken,
      [this](auto type) { return this->cekTipeToken(type); }
    ) // function any_of
  ) {
    return true;
  } // if
  return false;
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
      titik.tambahTitikTurunan(this->uraiPernyataan());
    } catch (const DataPengecualianSintaks &data) {
      this->pengecualianSintaks.tambahData(data);
      this->majuKeTokenSelanjutnya();
    } // catch
  } // while

  try {
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
        .pesan=__NK__LABEL_KELUARAN_PS__ "harus nya akhir dari file."
      }; // throw
    } // else
  } catch (const DataPengecualianSintaks &data) {
    this->pengecualianSintaks.tambahData(data);
  } // catch

  if(this->pengecualianSintaks.apaKahAdaData()) {
    this->pengecualianSintaks.perbaruiPesanSesuaiData();
    nusantara::cetak(this->pengecualianSintaks.what());
    exit(1);
  }

  this->hasilPenguraian = std::make_unique<Titik>(std::move(titik));
} // function uraikan

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiPernyataan() {
  auto titik = Titik{TipeTitik::PERNYATAAN};

  #ifdef __NK__SINTAKS_PERNYATAAN_DENGAN_TITIK_KOMA_WAJIB__
  auto makanTokenTitikKoma = [this] -> const Token & {
    return this->makanToken(
      TipeToken::titikKoma,
      __NK__LABEL_KELUARAN_PS__ "Jangan lupa titik koma."
    ); // fucntion makanToken
  }; // lambda makanTokenTitikKoma

  auto makanTokenTitikKomaMendukungPsa = [&makanTokenTitikKoma, this, &titik] -> void {
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
  };
  #endif

  if(this->cekTipeToken(TipeToken::identifikasi)) {
    titik.tambahTitikTurunan(this->uraiPanggilFungsi()); 
    #ifdef __NK__SINTAKS_PERNYATAAN_DENGAN_TITIK_KOMA_WAJIB__
    makanTokenTitikKomaMendukungPsa();
    #endif
  }else if(this->cekTipeToken({TipeToken::nilaiBilangan, TipeToken::nilaiTeks})) {  
    titik.tambahTitikTurunan(this->uraiEkspresi());
    #ifdef __NK__SINTAKS_PERNYATAAN_DENGAN_TITIK_KOMA_WAJIB__
    makanTokenTitikKomaMendukungPsa();
    #endif
  }else if(this->cekTipeToken(TipeToken::muat)) {
    this->makanToken(
      TipeToken::muat, 
      "Untuk memuat berkas, harus menggunakan kata kunci 'muat'."
    ); // function makanToken
    const auto& ekspresi = this->uraiEkspresi();
    #ifdef __NK__SINTAKS_PERNYATAAN_DENGAN_TITIK_KOMA_WAJIB__
    makanTokenTitikKoma();
    #endif
    const auto& token = ekspresi->ambilKumpulanTitikTurunan()[0]->ambilToken().value();
    throw DataPengecualianSintaks{
      .lokasiBerkas=token.lokasiBerkas,
      .lokasiToken=token.lokasi,
      .konten=token.konten,
      .pesan= __NK__LABEL_KELUARAN_PS__"Pengurai sintaks belum dapat memuat file external."
    };
  } else {
    throw DataPengecualianSintaks{
      .lokasiBerkas=this->tokenSaatIni().lokasiBerkas,
      .lokasiToken=this->tokenSaatIni().lokasi,
      .konten=this->tokenSaatIni().konten,
      .pesan= __NK__LABEL_KELUARAN_PS__
      #ifndef __NK__SINTAKS_PERNYATAAN_DENGAN_TITIK_KOMA_WAJIB__
      + std::string((this->tokenSaatIni().tipe == TipeToken::titikKoma) ? "Titik koma tidak di perlukan." : "Pernyataan gak benar.")
      #else
      "Pernyataan gak benar."
      #endif
    };
  } // else

  // Jika hanya ada 1 titik turunan saja itu yang akan di keluarkan.
  if(titik.ambilKumpulanTitikTurunan().size() == 1 && this->psa) {
    return titik.keluarKanTitikTurunan(0);
  }

  return std::make_unique<Titik>(std::move(titik));
} // function uraiPernyataan

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiPanggilFungsi() {
  auto titik = Titik{TipeTitik::PANGGIL_FUNGSI};

  titik.tambahTitikTurunan(
    std::make_unique<Titik>(
      Titik{
        TipeTitik::TOKEN, 
        this->makanToken(
          nusantara::TipeToken::identifikasi,
          __NK__LABEL_KELUARAN_PS__ "Nama fungsi belum dibuat."
        ) // function makanToken
      } // constructor Titik
    ) // constructor make_unique
  ); // function tambahTitikTurunan

  auto makanTokenKurungBulatBuka = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatBuka,
      __NK__LABEL_KELUARAN_PS__ "Tempat parameter pada fungsi harus ada kurung bulat buka '('."
    ); // function makanToken
  }; // lambda makanTokenKurungBulatBuka

  auto makanTokenKurungBulatTutup = [this] -> const nusantara::Token& {
    return this->makanToken(
      TipeToken::kurungBulatTutup,
      __NK__LABEL_KELUARAN_PS__ "Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
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
} // function uraiPanggilFungsi

std::unique_ptr<nusantara::Titik> nusantara::PenguraiSintaks::uraiEkspresi() {
  auto titik = Titik{TipeTitik::EKSPRESI};
  if(this->cekTipeToken(TipeToken::nilaiBilangan)) {
    titik.tambahTitikTurunan(
      std::make_unique<Titik>(Titik{
        TipeTitik::TOKEN,
        this->makanToken(
          TipeToken::nilaiBilangan, 
          "Bukanlah sebuah bilangan."
        ) // function makanToken
      }) // constructor make_unique
    ); // function tambahTitikTurunan
  } else if(this->cekTipeToken(TipeToken::nilaiTeks)) {
    titik.tambahTitikTurunan(
      std::make_unique<Titik>(Titik{
        TipeTitik::TOKEN,
        this->makanToken(
          TipeToken::nilaiTeks, 
          "Bukanlah sebuah teks."
        ) // function makanToken
      }) // constructor make_unique
    ); // function tambahTitikTurunan
  } else{
    throw DataPengecualianSintaks{
      .lokasiBerkas=this->tokenSaatIni().lokasiBerkas,
      .lokasiToken=this->tokenSaatIni().lokasi,
      .konten=this->tokenSaatIni().konten,
      .pesan=__NK__LABEL_KELUARAN_PS__ "Ekspresi tidak benar."
    }; // throw
  } // else

  return std::make_unique<Titik>(std::move(titik));
} // fungsi uraiNilaiBilangan

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