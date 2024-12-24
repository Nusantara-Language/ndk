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
#include "semantic_analyzer/semantic_analyzer.hpp"
#include "interpreter/interpreter.hpp"
#include "perintah/perintah.hpp"
#include "parser/parser.hpp"
#include "lexer/lexer.hpp"
#include "cetak/cetak.hpp"
#include "version.hpp"
#include <config.hpp>

#ifdef SHOW_WAKTU_EKSEKUSI
  #include <waktu_eksekusi/waktu_eksekusi.hpp>
#endif


auto info(nusantara::EksekusiPerintah& eksekusiPerintah, size_t& indeksSaatIni, std::vector<std::string>& argumen) -> void {
  nstd::cetakDBB("Penggunaan: nusantara <perintah> [argumen]\n");
  nstd::cetakDBB("Perintah yang tersedia:");

  for (const auto& perintah : eksekusiPerintah.ambilKumpulanPerintah()) {
    bool iniPerintahAwal = perintah.ambilNama() == eksekusiPerintah.ambilKumpulanPerintah().begin()->ambilNama();
    nstd::cetakDF("{}{}", (iniPerintahAwal ? " " : "\n "), perintah.ubahKeString());
  }
}

auto versi(nusantara::EksekusiPerintah&, size_t &, std::vector<std::string>&) -> void {
  nstd::cetakDF("nusantara v{}", VERSION);
}

auto prosesBerkasLexer(const std::string &lokasFile) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.baca(lokasFile)) {
    return;
  }

  lexer.tokenisasi();
  lexer.cetak();
}

auto prosesBerkasPengurai(const std::string &lokasiFile, const bool& ast = false) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.baca(lokasiFile)) {
    return;
  }

  lexer.tokenisasi();

  nusantara::Parser parser(ast);

  parser.ambilKumpulanToken(lexer.ambilHasil());
  parser.parsing();
  parser.print();
}

auto prosesBerkasPenerjemah(const std::string &lokasiFile) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.baca(lokasiFile)) {
    return;
  }

  lexer.tokenisasi();

  nusantara::Parser parser(true);
  parser.ambilKumpulanToken(lexer.ambilHasil());
  parser.parsing();

  nusantara::SemanticAnalyzer semanticAnalyzer;
  if(!parser.getResult()->accept(semanticAnalyzer)) return;

  nusantara::Interpreter interpreter;
  parser.getResult()->accept(interpreter);
}

auto prosesBerkas(
  nusantara::EksekusiPerintah&  /*eksekusiPerintah*/,
  size_t &indeksSaatIni,
  std::vector<std::string>& argumen
) -> void {
  std::string lokasiFile = argumen[indeksSaatIni];
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());
  
  if(argumen.size() < 3) {
    argumen.emplace_back("-i"); // Default mode interpreter
  }

  indeksSaatIni++;

  if(argumen.size() == 3) {
    // Lexer mode
    if(argumen[indeksSaatIni] == "-t") {
      prosesBerkasLexer(lokasiFile);
      return;
    }

    // Parser mode
    if(argumen[indeksSaatIni] == "-u") {
      prosesBerkasPengurai(lokasiFile);
      return;
    }

    // Parser Ast mode
    if(argumen[indeksSaatIni] == "-psa") {
      prosesBerkasPengurai(lokasiFile, true);
      return;
    }

    // Interpreter mode
    if(argumen[indeksSaatIni] == "-p") {
      prosesBerkasPenerjemah(lokasiFile);
      return;
    }
  }

  nstd::cetakDF("Argumen '{}' tidak dikenali", argumen[indeksSaatIni]);
}

auto main(int argc, const char* argv[]) -> int {

  #ifdef SHOW_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::mulai();
  #endif

  nusantara::EksekusiPerintah eksekusiPerintah;

  eksekusiPerintah.tambah({
    "info",
    "Untuk melihat informasi.",
    info,
    true,
  });

  eksekusiPerintah.tambah({
    "versi",
    "Untuk melihat versi.",
    versi,
    true,
  });

  eksekusiPerintah.tambah({
    std::regex(".*\\.n"),
    "filename.n",
    "Untuk mengolah file nusantara.",
    prosesBerkas,
    false,
  });

  eksekusiPerintah.eksekusi({argv, argv + argc});

  #ifdef SHOW_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::selesai();
    nstd::WaktuEksekusi::cetak();
  #endif

  return 0;
}