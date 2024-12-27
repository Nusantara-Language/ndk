/*
 * ----------------------------------------------------------------------------
 * Project: Nusantara Language
 * Author: Fern Aerell
 * License: BSD 3-Clause License
 * Copyright (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <regex>
#include <stdexcept>
#include <string>

#include "catatan/catatan.ap.hpp"
#include "token/kumpulan_token_regex/token_regex_nusantara.hpp"
#include "penganalisis_semantik/penganalisis_semantik.hpp"
#include "konfig/konfig_argumen_proses_berkas.hpp"
#include "konfig/konfig_ekstensi_berkas.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "penafsir/penafsir.hpp"
#include "cetak/cetak.hpp"
#include <konfig/konfig.hpp>
#include <utility>
#include "konfig/versi.hpp"
#include "alat.hpp"

#include "argparse/argparse.hpp"

#ifdef PERLIHATKAN_WAKTU_EKSEKUSI
  #include <waktu_eksekusi/waktu_eksekusi.hpp>
#endif

auto main(int argc, const char* argv[]) -> int {

  #ifdef PERLIHATKAN_WAKTU_EKSEKUSI

    auto programBerakhir = []() {
      nusantara::WaktuEksekusi::selesai();
      nusantara::WaktuEksekusi::cetak();
    }; // lambda programBerakhir

    nusantara::WaktuEksekusi::mulai();

    if(atexit(programBerakhir) != 0) {
      __CATATAN__KESALAHAN__("Gagal mendaftarkan fungsi programBerakhir!");
      exit(1);
    }
  #endif

  argparse::ArgumentParser program(
    "nusantara",
    VERSI,
    argparse::default_arguments::none,
    true,
    std::cout
  );

  program.set_usage_break_on_mutex();

  program.add_argument("-i", "--info")
    .help("Untuk menampilkan informasi.")
    .default_value(false)
    .implicit_value(true)
    .nargs(0)
    .action([&program](const std::string&) {
      nusantara::cetak(program.help().str());
      exit(0);
    }); // function action

  program.add_argument("-v", "--versi")
    .help("Untuk menampilkan versi.")
    .default_value(false)
    .implicit_value(true)
    .nargs(0)
    .action([&program](const std::string& nilai) {
      nusantara::cetakDBBDF("nusantara v{}{}", VERSI, nilai);
      exit(0);
    }); // function action

  program.add_usage_newline();

  program.add_argument("<berkas.n>")
    .help("Untuk mengolah berkas nusantara.")
    .nargs(1)
    .required()
    .action([](const std::string& lokasiBerkas) {
      #ifdef __NK__EKSTENSI_BERKAS_WAJIB__
      if(!std::regex_match(lokasiBerkas, std::regex(__NK__EKSTENSI_BERKAS_REGEX__))) {
        throw std::runtime_error("Ekstensi berkas harus '." __NK__EKSTENSI_BERKAS__ "'");
      }
      #endif
      return std::pair<std::string, std::string>({
        lokasiBerkas,
        nusantara::bacaBerkasDalamBentukString(lokasiBerkas)
      });
    });

  auto &argumenProsesBerkas = program.add_mutually_exclusive_group();
  
  argumenProsesBerkas.add_argument(__NK__ARGUMEN_PROSES_BERKAS_TS__)
    .help("Untuk melakukan tokenisasi berkas nusantara.")
    .nargs(2)
    .default_value(false)
    .implicit_value(true)
    .flag();

  argumenProsesBerkas.add_argument(__NK__ARGUMEN_PROSES_BERKAS_AS__)
    .help("Untuk melakukan analisis semantik berkas nusantara.")
    .nargs(2)
    .default_value(false)
    .implicit_value(true)
    .flag();

  argumenProsesBerkas.add_argument(__NK__ARGUMEN_PROSES_BERKAS_PS__)
    .help("Untuk mengurai berkas nusantara.")
    .nargs(2)
    .default_value(false)
    .implicit_value(true)
    .flag();

  argumenProsesBerkas.add_argument(__NK__ARGUMEN_PROSES_BERKAS_PSA__)
    .help("Untuk mengurai berkas nusantara.")
    .nargs(2)
    .default_value(false)
    .implicit_value(true)
    .flag();

  argumenProsesBerkas.add_argument(__NK__ARGUMEN_PROSES_BERKAS_P__)
    .help("Untuk menafsirkan berkas nusantara.")
    .nargs(2)
    .default_value(false)
    .implicit_value(true)
    .flag();

  try {
    program.parse_args(argc, argv);
  } catch (const std::exception& kesalahan) {
    nusantara::cetakDBB(kesalahan.what());
    nusantara::cetak(program);
    exit(1);
  } // catch

  if(argc == 1) {
    nusantara::cetak(program);
    exit(0);
  } // if

  auto berkas = program.get<std::pair<std::string, std::string>>("<berkas.n>");
  auto tsArg = program.get<bool>(__NK__ARGUMEN_PROSES_BERKAS_TS__);
  auto psArg = program.get<bool>(__NK__ARGUMEN_PROSES_BERKAS_PS__);
  auto psaArg = program.get<bool>(__NK__ARGUMEN_PROSES_BERKAS_PSA__);
  auto asArg = program.get<bool>(__NK__ARGUMEN_PROSES_BERKAS_AS__);
  auto pArg = program.get<bool>(__NK__ARGUMEN_PROSES_BERKAS_P__);

  if(berkas.second.empty()) {
    exit(0);
  } // if

  auto pemecahSintaks = nusantara::PemecahSintaks(nusantara::nusantaraTokenRegexs());
  pemecahSintaks.aturLokasiBerkas(berkas.first);
  pemecahSintaks.aturKonten(berkas.second);
  pemecahSintaks.tokenisasi();

  if(tsArg) {
    pemecahSintaks.cetak();
    exit(0);
  } // if

  auto penguraiSintaks = nusantara::PenguraiSintaks( psaArg ? psaArg : psArg ? false : true);
  penguraiSintaks.aturKumpulanToken(pemecahSintaks.ambilHasil());
  penguraiSintaks.uraikan();

  if(psArg || psaArg) {
    penguraiSintaks.cetak();
    exit(0);
  } // if

  auto penganalisisSemantik = nusantara::PenganalisisSemantik();
  penguraiSintaks.ambilHasil()->terima(penganalisisSemantik);

  if(asArg) {
    exit(0);
  } // if

  auto penafsir = nusantara::Penafsir();
  penguraiSintaks.ambilHasil()->terima(penafsir);
  if(pArg) {
    exit(0);
  } // if

  return 0;
} // function main