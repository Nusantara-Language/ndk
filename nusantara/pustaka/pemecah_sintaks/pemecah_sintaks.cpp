/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <iosfwd>
#include <string>
#include <vector>
#include <regex>
#include <ios>

#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "token/tipe_token.hpp"

bool nusantara::PemecahSintaks::bacaBerkas(std::string lokasiBerkas) {
  this->lokasiBerkas = std::move(lokasiBerkas);
  std::ifstream file(this->lokasiBerkas);
  if (!file.is_open()) {
    std::cerr << "Tidak dapat membuka file '" << this->lokasiBerkas << "'\n";
    return false;
  } // if

  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();
  if (fileSize < 0) {
    std::cerr << "Error: Ukuran file '" << this->lokasiBerkas << "' tidak valid.\n";
    return false;
  } // if

  this->konten.resize(static_cast<std::size_t>(fileSize));

  file.seekg(0, std::ios::beg);
  file.read(this->konten.data(), static_cast<std::streamsize>(this->konten.size()));
  file.close();
  return true;
} // function bacaBerkas

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

  if (!std::regex_search(this->konten, dataYangSama, std::regex(""))) {
    std::cerr << "[PS] Tidak dapat membuat token dari konten.\n";
    return;
  } // if
} // function buatToken

void nusantara::PemecahSintaks::buatBanyakToken() {
  while (this->konten.size() > 0) {
    Token token;
    this->buatToken(token);
    if (token.tipe != TipeToken::ruangKosong && token.tipe != TipeToken::barisBaru && token.tipe && token.tipe != TipeToken::tidakDiketahui) {
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
} // function tokenisasi

void nusantara::PemecahSintaks::cetak() {
  for (auto& token : this->hasilTokenisasi) {
    std::cout << token.lokasiBerkas << ":"
              << token.lokasi.baris << ":"
              << token.lokasi.kolom << " "
              << tipeTokenKeString(token.tipe) << " => "
              << token.konten << "\n";
  } // for
} // function cetak