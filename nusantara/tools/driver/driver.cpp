#define SHOW_WAKTU_EKSEKUSI

#include <cstddef>
#include <regex>
#include <string>
#include <vector>

#ifdef SHOW_WAKTU_EKSEKUSI

  #include <waktu_eksekusi/waktu_eksekusi.hpp>

#endif

#include "token/kumpulan_token_regex/token_regex_nusantara.hpp"

#include "cetak/cetak.hpp"
#include "command/command.hpp"
#include "interpreter/interpreter.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"
#include "version.hpp"

auto info(
  nusantara::CommandExecutor& cExec,
  size_t & /*currentIndex*/,
  std::vector<std::string>&  /*args*/
) -> void {
  nstd::cetakDBB("Penggunaan: nusantara <perintah> [argumen]\n");
  nstd::cetakDBB("Perintah yang tersedia:");

  for(const auto& arg: cExec.getCommands()) {
    bool isBegin = arg.getName() == cExec.getCommands().begin()->getName();
    nstd::cetakDF(
      "{}{}", 
      isBegin ? " " : "\n ", 
      arg.toString()
    );
  }
}

auto versi(
  nusantara::CommandExecutor&  /*cExec*/,
  size_t & /*currentIndex*/,
  std::vector<std::string>&  /*args*/
) -> void {
  nstd::cetakDF("nusantara v{}", VERSION);
}

auto fileProccesingLexer(const std::string &filepath) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.read(filepath)) {
    return;
  }

  lexer.tokenization();
  lexer.print();
}

auto fileProccesingParser(const std::string &filepath) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.read(filepath)) {
    return;
  }

  lexer.tokenization();

  nusantara::Parser parser(false);

  parser.setTokens(lexer.getResult());
  parser.parsing();
  parser.print();
}

auto fileProccesingInterpreter(const std::string &filepath) -> void {
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());

  if(!lexer.read(filepath)) {
    return;
  }

  lexer.tokenization();

  nusantara::Parser parser(true);
  parser.setTokens(lexer.getResult());
  parser.parsing();

  nusantara::Interpreter::interpretation(parser.getResult());
}

auto fileProccesing(
  nusantara::CommandExecutor&  /*cExec*/,
  size_t &currentIndex,
  std::vector<std::string>& args
) -> void {
  std::string filepath = args[currentIndex];
  nusantara::Lexer lexer(nusantara::nusantaraTokenRegexs());
  
  if(args.size() < 3) {
    args.emplace_back("-i"); // Default mode interpreter
  }

  currentIndex++;

  if(args.size() == 3) {
    // Lexer mode
    if(args[currentIndex] == "-l") {    
      fileProccesingLexer(filepath);
      return;
    }

    // Parser mode
    if(args[currentIndex] == "-p") {
      fileProccesingParser(filepath);
      return;
    }

    // Interpreter mode
    if(args[currentIndex] == "-i") {
      fileProccesingInterpreter(filepath);
      return;
    }
  }

  nstd::cetakDF("Argumen '{}' tidak dikenali", args[currentIndex]);
}

auto main(int argc, const char* argv[]) -> int {

  #ifdef SHOW_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::mulai();
  #endif

  nusantara::CommandExecutor cExec;

  cExec.add({
    "info",
    "Untuk melihat informasi.",
    info,
    true,
  });

  cExec.add({
    "versi",
    "Untuk melihat versi.",
    versi,
    true,
  });

  cExec.add({
    std::regex(".*\\.n"),
    "filename.n",
    "Untuk mengolah file nusantara.",
    fileProccesing,
    false,
  });

  cExec.execute({argv, argv + argc});

  #ifdef SHOW_WAKTU_EKSEKUSI
    nstd::WaktuEksekusi::selesai();
    nstd::WaktuEksekusi::cetak();
  #endif

  return 0;
}