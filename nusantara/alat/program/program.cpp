/*
 * ----------------------------------------------------------------------------
 * Project: Nusantara Language
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <regex>
#include <string>

#include "token/kumpulan_token_regex/token_regex_nusantara.hpp"
#include "penganalisis_semantik/penganalisis_semantik.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "penafsir/penafsir.hpp"
#include "perintah/perintah.hpp"
#include "cetak/cetak.hpp"
#include <konfig.hpp>
#include "versi.hpp"

#ifdef PERLIHATKAN_WAKTU_EKSEKUSI
  #include <waktu_eksekusi/waktu_eksekusi.hpp>
#endif

void info(nusantara::EksekusiPerintah& eksekusiPerintah, size_t& indeksSaatIni, std::vector<std::string>& argumen) {
  nstd::cetakDBB("Penggunaan: nusantara <perintah> [argumen]\n");
  nstd::cetakDBB("Perintah yang tersedia:");

  for (const auto& perintah : eksekusiPerintah.ambilKumpulanPerintah()) {
    bool iniPerintahAwal = perintah.ambilNama() == eksekusiPerintah.ambilKumpulanPerintah().begin()->ambilNama();
    nstd::cetakDF("{}{}", (iniPerintahAwal ? " " : "\n "), perintah.ubahKeString());
  } // for
} // function info

void versi(nusantara::EksekusiPerintah&, size_t &, std::vector<std::string>&) {
  nstd::cetakDF("nusantara v{}", VERSI);
} // function versi

void prosesBerkasLexer(const std::string &lokasFile) {
  nusantara::PemecahSintaks lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.bacaBerkas(lokasFile)) {
    return;
  } // if

  lexer.tokenisasi();
  lexer.cetak();
} // function prosesBerkasLexer

void prosesBerkasPengurai(const std::string &lokasiFile, const bool& psa = false) {
  nusantara::PemecahSintaks pemecahSintaks(nusantara::nusantaraTokenRegexs());

  if(!pemecahSintaks.bacaBerkas(lokasiFile)) {
    return;
  } // if

  pemecahSintaks.tokenisasi();

  nusantara::PenguraiSintaks penguraiSintaks(psa);

  penguraiSintaks.aturKumpulanToken(pemecahSintaks.ambilHasil());
  penguraiSintaks.uraikan();
  penguraiSintaks.cetak();
} // function prosesBerkasPengurai

void prosesBerkasPenerjemah(const std::string &lokasiFile) {
  nusantara::PemecahSintaks pemecahSintaks(nusantara::nusantaraTokenRegexs());

  if(!pemecahSintaks.bacaBerkas(lokasiFile)) {
    return;
  } // if

  pemecahSintaks.tokenisasi();

  nusantara::PenguraiSintaks penguraiSintaks(true);

  penguraiSintaks.aturKumpulanToken(pemecahSintaks.ambilHasil());
  penguraiSintaks.uraikan();

  nusantara::PenganalisisSemantik penganalisisSemantik;
  if(!penguraiSintaks.ambilHasil()->terima(penganalisisSemantik)) return;

  nusantara::Penafsir penafsir;
  penguraiSintaks.ambilHasil()->terima(penafsir);
}

void prosesBerkas(
  nusantara::EksekusiPerintah&,
  size_t &indeksSaatIni,
  std::vector<std::string>& argumen
) {
  std::string lokasiFile = argumen[indeksSaatIni];
  nusantara::PemecahSintaks lexer(nusantara::nusantaraTokenRegexs());
  
  if(argumen.size() < 3) {
    argumen.emplace_back("-p");
  } // if

  indeksSaatIni++;

  if(argumen.size() == 3) {
    // Lexer mode
    if(argumen[indeksSaatIni] == "-t") {
      prosesBerkasLexer(lokasiFile);
      return;
    } // if

    // Parser mode
    if(argumen[indeksSaatIni] == "-u") {
      prosesBerkasPengurai(lokasiFile);
      return;
    } // if

    // Parser Ast mode
    if(argumen[indeksSaatIni] == "-psa") {
      prosesBerkasPengurai(lokasiFile, true);
      return;
    } // if

    // Interpreter mode
    if(argumen[indeksSaatIni] == "-p") {
      prosesBerkasPenerjemah(lokasiFile);
      return;
    } // if
  } // if

  nstd::cetakDF("Argumen '{}' tidak dikenali", argumen[indeksSaatIni]);
} // function prosesBerkas

auto main(int argc, const char* argv[]) -> int {

  #ifdef PERLIHATKAN_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::mulai();
  #endif

  nusantara::EksekusiPerintah eksekusiPerintah;

  eksekusiPerintah.tambah({
    "info",
    "Untuk melihat informasi.",
    info,
    true,
  }); // function tambah

  eksekusiPerintah.tambah({
    "versi",
    "Untuk melihat versi.",
    versi,
    true,
  }); // function tambah

  eksekusiPerintah.tambah({
    std::regex(".*\\.n"),
    "filename.n",
    "Untuk mengolah file nusantara.",
    prosesBerkas,
    false,
  }); // function tambah

  eksekusiPerintah.eksekusi({argv, argv + argc});

  #ifdef PERLIHATKAN_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::selesai();
    nstd::WaktuEksekusi::cetak();
  #endif

  return 0;
} // function main