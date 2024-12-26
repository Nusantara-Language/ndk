/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include <regex>

#include "alat.hpp"
#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "konfig/konfig_label_keluaran.hpp"
#include "token/tipe_token.hpp"
#include "cetak/cetak.hpp"

void nusantara::PemecahSintaks::aturLokasiBerkas(const std::string& lokasiBerkas) {
  this->lokasiBerkas = lokasiBerkas;
} // function aturLokasiBerkas
      
void nusantara::PemecahSintaks::aturKonten(const std::string& konten) {
  this->konten = nusantara::hapusRuangKosongDiAwalDanAkhirString(konten);
} // function aturKonten

void nusantara::PemecahSintaks::buatToken(Token& token) {
  std::smatch dataYangSama;
  for (const TokenRegex& tokenRegex : this->tokenRegexs) {
    if (std::regex_search(this->konten, dataYangSama, tokenRegex.ambilRegex())) {
      this->membuatToken(dataYangSama, tokenRegex.ambilTipe(), token);

      if (tokenRegex.ambilTipe() == TipeToken::barisBaru) {
        this->lokasiToken.baris++;
        this->lokasiToken.kolom = 1;
      } // if

      break;
    } // if
  } // for
} // function buatToken

void nusantara::PemecahSintaks::buatBanyakToken() {
  while (this->konten.size() > 0) {
    Token token;
    this->buatToken(token);
    if(token.tipe == TipeToken::tidakDiketahui) {
      this->pengecualianSintaks.tambahData({
          token.lokasiBerkas, 
          token.lokasi, 
          token.konten, 
          __NK__LABEL_KELUARAN_PS "Karakter tidak di ketahui."
      }); // function tambahData
    }else if (token.tipe != TipeToken::ruangKosong && token.tipe != TipeToken::barisBaru) {
      this->hasilTokenisasi.push_back(std::move(token));
    } // if

  } // while

  Token tokenAkhir;
  tokenAkhir.lokasiBerkas = this->lokasiBerkas;
  tokenAkhir.lokasi.baris = this->lokasiToken.baris;
  tokenAkhir.lokasi.kolom = this->lokasiToken.kolom - this->lokasiToken.baris + 1;
  tokenAkhir.tipe = TipeToken::akhirDariFile;
  this->hasilTokenisasi.push_back(std::move(tokenAkhir));
} // function buatBanyakToken

void nusantara::PemecahSintaks::membuatToken(const std::smatch& dataYangSama, const TipeToken& tipeToken, Token& token) {
  std::string contentTemp = dataYangSama.str();
  token.lokasiBerkas = this->lokasiBerkas;
  token.lokasi.baris = this->lokasiToken.baris;
  token.lokasi.kolom = this->lokasiToken.kolom;
  token.konten = contentTemp;
  token.tipe = tipeToken;

  this->lokasiToken.kolom += dataYangSama.length();
  this->konten.erase(dataYangSama.position(), dataYangSama.length());
} // function membuatToken

const std::vector<nusantara::Token>& nusantara::PemecahSintaks::ambilHasil() const {
  return this->hasilTokenisasi;
} // function ambilHasil

void nusantara::PemecahSintaks::tokenisasi() {
  this->buatBanyakToken();

  if(this->pengecualianSintaks.apaKahAdaData()) {
    this->pengecualianSintaks.perbaruiPesanSesuaiData();
    nusantara::cetak(this->pengecualianSintaks.what());
    exit(1);
  }
} // function tokenisasi

void nusantara::PemecahSintaks::cetak() {
  for (auto& token : this->hasilTokenisasi) {
    nusantara::cetakDBB(token.ubahKeString());
  } // for
} // function cetak