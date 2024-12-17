#include "parser.hpp"

#include <iostream>

#include <lexer.hpp>

#include <memory>

#include <span>
#include <string>
#include <vector>

auto main(int argc, const char *argv[]) -> int {
  std::cout << "Nusantara Language Parser" << "\n\n";

  std::span<const char *> args(argv, argc);
  if (argc < 2) {
    std::cerr << "Penggunaan " << args[0] << " <nama_file>" << "\n";
    return 1;
  }

  std::string content;
  lexer::TokenLocation location{1, 1};
  lexer::muatFile(args[1], content);

  std::vector<lexer::Token> tokens;

  lexer::generateTokens(args[1], location, content, tokens);

  Parser::ParseNode parser(tokens);

  auto parseNodes = parser.parse();

  std::cout << "Hasil parse:" << "\n";
  if (parseNodes != nullptr) {
    Parser::coutNode(*parseNodes, 0);
  }

  return 0;
}