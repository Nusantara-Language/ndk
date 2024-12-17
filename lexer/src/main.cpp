// Include STD C++
#include <iomanip>
#include <iostream>
#include <span>
#include <string>
#include <vector>

// Include project file header
#include "lexer.hpp"

// Function
auto main(int argc, const char* argv[]) -> int {
  std::cout << "Nusantara Language Lexer" << "\n\n";

  std::span<const char *> args(argv, argc);

  if (argc < 2) {
    std::cerr << "Penggunaan " << args[0] << " <nama_file>" << "\n";
    return 1;
  }

  std::string content;
  lexer::TokenLocation location(1, 1);
  std::vector<lexer::Token> tokens;

  lexer::muatFile(args[1], content);
  lexer::generateTokens(args[1], location, content, tokens);

  const int filenameWidth = 12;
  const int lineWidth = 1;
  const int indexWidth = 5;
  const int typeWidth = 23;
  const int contentWidth = 10;

  for (auto &token : tokens) {
    std::cout << std::setw(filenameWidth) 
    << std::left 
    << token.fileName 
    << ":"
    << std::setw(lineWidth) 
    << std::left 
    << token.location.row 
    << ":"
    << std::setw(indexWidth) 
    << std::left 
    << token.location.column
    << " " 
    << std::setw(typeWidth) 
    << std::left
    << lexer::tokenTypeToString(token.type) 
    << " => "
    << std::setw(contentWidth) 
    << std::left 
    << token.content 
    << "\n";
  }

  return 0;
}