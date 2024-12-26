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
#include "konfig/konfig_argumen_proses_berkas.hpp"
#include "konfig/konfig_ekstensi_berkas.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "penafsir/penafsir.hpp"
#include "perintah/perintah.hpp"
#include "cetak/cetak.hpp"
#include <konfig/konfig.hpp>
#include "konfig/versi.hpp"
#include "alat.hpp"

#ifdef PERLIHATKAN_WAKTU_EKSEKUSI
  #include <waktu_eksekusi/waktu_eksekusi.hpp>
#endif

void info(nusantara::EksekusiPerintah& eksekusiPerintah, size_t& indeksSaatIni, std::vector<std::string>& argumen) {
  nusantara::cetakDBB("Penggunaan: nusantara <perintah> [argumen]\n");
  nusantara::cetakDBB("Perintah yang tersedia:");

  for (const auto& perintah : eksekusiPerintah.ambilKumpulanPerintah()) {
    bool iniPerintahAwal = perintah.ambilNama() == eksekusiPerintah.ambilKumpulanPerintah().begin()->ambilNama();
    nusantara::cetakDF("{}{}", (iniPerintahAwal ? " " : "\n "), perintah.ubahKeString());
  } // for
} // function info

void versi(nusantara::EksekusiPerintah&, size_t &, std::vector<std::string>&) {
  nusantara::cetakDF("nusantara v{}", VERSI);
} // function versi

void prosesBerkasPemecahSintaks(const std::string &lokasiFile) {
  nusantara::PemecahSintaks pemecahSintaks(nusantara::nusantaraTokenRegexs());

  pemecahSintaks.aturLokasiBerkas(lokasiFile);
  pemecahSintaks.aturKonten(nusantara::bacaBerkasDalamBentukString(lokasiFile));

  pemecahSintaks.tokenisasi();
  pemecahSintaks.cetak();
} // function prosesBerkasLexer

void prosesBerkasPenguraiSintaks(const std::string &lokasiFile, const bool& psa = false) {
  nusantara::PemecahSintaks pemecahSintaks(nusantara::nusantaraTokenRegexs());

  pemecahSintaks.aturLokasiBerkas(lokasiFile);
  pemecahSintaks.aturKonten(nusantara::bacaBerkasDalamBentukString(lokasiFile));

  pemecahSintaks.tokenisasi();

  nusantara::PenguraiSintaks penguraiSintaks(psa);

  penguraiSintaks.aturKumpulanToken(pemecahSintaks.ambilHasil());
  penguraiSintaks.uraikan();
  penguraiSintaks.cetak();
} // function prosesBerkasPengurai

void prosesBerkasPenerjemah(const std::string &lokasiFile) {
  nusantara::PemecahSintaks pemecahSintaks(nusantara::nusantaraTokenRegexs());

  pemecahSintaks.aturLokasiBerkas(lokasiFile);
  pemecahSintaks.aturKonten(nusantara::bacaBerkasDalamBentukString(lokasiFile));

  pemecahSintaks.tokenisasi();

  nusantara::PenguraiSintaks penguraiSintaks(true);

  penguraiSintaks.aturKumpulanToken(pemecahSintaks.ambilHasil());
  penguraiSintaks.uraikan();

  nusantara::PenganalisisSemantik penganalisisSemantik;
  penguraiSintaks.ambilHasil()->terima(penganalisisSemantik);

  nusantara::Penafsir penafsir;
  penguraiSintaks.ambilHasil()->terima(penafsir);
}

void prosesBerkas(
  nusantara::EksekusiPerintah&,
  size_t &indeksSaatIni,
  std::vector<std::string>& argumen
) {
  std::string lokasiFile = argumen[indeksSaatIni];
  
  if(argumen.size() < 3) {
    argumen.emplace_back(__NK__ARGUMEN_PROSES_BERKAS_P);
  } // if

  indeksSaatIni++;

  if(argumen.size() == 3) {
    // Lexer mode
    if(argumen[indeksSaatIni] == __NK__ARGUMEN_PROSES_BERKAS_TS) {
      prosesBerkasPemecahSintaks(lokasiFile);
      return;
    } // if

    // Parser mode
    if(argumen[indeksSaatIni] == __NK__ARGUMEN_PROSES_BERKAS_PS) {
      prosesBerkasPenguraiSintaks(lokasiFile);
      return;
    } // if

    // Parser Ast mode
    if(argumen[indeksSaatIni] == __NK__ARGUMEN_PROSES_BERKAS_PSA) {
      prosesBerkasPenguraiSintaks(lokasiFile, true);
      return;
    } // if

    // Interpreter mode
    if(argumen[indeksSaatIni] == __NK__ARGUMEN_PROSES_BERKAS_P) {
      prosesBerkasPenerjemah(lokasiFile);
      return;
    } // if
  } // if

  nusantara::cetakDF("Argumen '{}' tidak dikenali", argumen[indeksSaatIni]);
} // function prosesBerkas

auto main(int argc, const char* argv[]) -> int {

  #ifdef PERLIHATKAN_WAKTU_EKSEKUSI
    nusantara::WaktuEksekusi::mulai();
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
    #ifdef __NK__EKSTENSI_BERKAS_WAJIB
      std::regex(__NK__EKSTENSI_BERKAS_REGEX),
      "filename." __NK__EKSTENSI_BERKAS,
    #else
      std::regex(".*"),
      "filename",
    #endif
    "Untuk mengolah file nusantara.",
    prosesBerkas,
    false,
  }); // function tambah

  eksekusiPerintah.eksekusi({argv, argv + argc});

  #ifdef PERLIHATKAN_WAKTU_EKSEKUSI
    nusantara::WaktuEksekusi::selesai();
    nusantara::WaktuEksekusi::cetak();
  #endif

  return 0;
} // function main