// Include STD C++
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

// Include project file header
#include "lexer/lexer.hpp"

auto nusantara::Lexer::read(std::string filepath) -> bool 
{
  this->filepath = std::move(filepath);
  std::ifstream file(this->filepath);
  if (!file.is_open()) {
    std::cerr << "Tidak dapat membuka file '" << this->filepath << "'\n";
    return false;
  }

  // Pindah ke akhir file untuk mendapatkan ukuran
  file.seekg(0, std::ios::end);
  std::streampos fileSize = file.tellg();
  if (fileSize < 0) {
    std::cerr << "Error: Ukuran file '" << this->filepath << "' tidak valid.\n";
    return false;
  }

  content.resize(static_cast<std::size_t>(fileSize));

  file.seekg(0, std::ios::beg);
  file.read(content.data(), static_cast<std::streamsize>(content.size()));
  file.close();
  return true;
}

auto nusantara::Lexer::generateToken(Token& token) -> void 
{
  std::smatch matches;
  for (const TokenRegex& tokenRegex : this->tokenRegexs) {
    if (std::regex_search(content, matches, tokenRegex.getRegex())) {
      createToken(matches, tokenRegex.getType(), token);
      if (tokenRegex.getType() == TokenType::barisBaru) {
        tokenLocation.row++;
        tokenLocation.column = 1;
      }
      break;
    }
  }
}

auto nusantara::Lexer::generateTokens() -> void 
{
  while (content.size() > 0) {
    Token token;
    generateToken(token);
    if (token.type != TokenType::ruangKosong && token.type != TokenType::barisBaru && token.type != TokenType::tidakDiketahui) {
      tokenizationResult.push_back(std::move(token));
    }
  }

  tokenizationResult.push_back({
    filepath,
    {tokenLocation.row, tokenLocation.column - tokenLocation.row + 1},
    TokenType::akhirDariFile,
    ""
  });
}

auto nusantara::Lexer::createToken(const std::smatch& matches, const TokenType& tokenType, Token& token) -> void 
{
  std::string contentTemp = matches.str();
  token.filePath = filepath;
  token.location.row = tokenLocation.row;
  token.location.column = tokenLocation.column;
  token.content = contentTemp;
  token.type = tokenType;

  tokenLocation.column += matches.length();
  content.erase(matches.position(), matches.length());
}

auto nusantara::Lexer::getResult() const -> const std::vector<Token>& 
{
  return tokenizationResult;
}

auto nusantara::Lexer::tokenization() -> void 
{
  generateTokens();
}

auto nusantara::Lexer::print() -> void 
{
  for (auto& token : tokenizationResult) {
    std::cout << token.filePath << ":"
              << token.location.row << ":"
              << token.location.column << " "
              << tokenTypeToString(token.type) << " => "
              << token.content << "\n";
  }
}