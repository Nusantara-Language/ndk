// Include STD C++
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

// Include project file header
#include "lexer.hpp"

// Getter function for class TokenRegex
auto lexer::TokenRegex::getRegex() const -> const std::regex & { return this->regex; }

auto lexer::TokenRegex::getType() const -> const TokenType & { return this->type; }

// Operator function for class TokenRegex
auto lexer::TokenRegex::operator<(const TokenRegex &other) const -> bool {
  return this->type < other.type;
}

auto lexer::TokenRegex::operator>(const TokenRegex &other) const -> bool {
  return this->type > other.type;
}

// Function global for namespace lexer
auto lexer::tokenRegexs() -> const std::set<lexer::TokenRegex> & {
  const static std::set<TokenRegex> result = {
    lexer::TokenRegex{
      std::regex("^[(]"), 
      lexer::TokenType::kurungBulatBuka
    },
    lexer::TokenRegex{
      std::regex("^[)]"), 
      lexer::TokenType::kurungBulatTutup
    },
    lexer::TokenRegex{
      std::regex("^[\n]"), 
      lexer::TokenType::barisBaru},
    lexer::TokenRegex{
      std::regex("^\\s"), 
      lexer::TokenType::ruangKosong
    },
    lexer::TokenRegex{
      std::regex("^;"), 
      lexer::TokenType::titikKoma
    },
    lexer::TokenRegex{
      std::regex("^[a-zA-Z][a-zA-Z0-9_]*"),
      lexer::TokenType::identifikasi
    },
    lexer::TokenRegex{
      std::regex("^."), 
      lexer::TokenType::tidakDiketahui
    },
  };
  return result;
};

auto lexer::tokenTypeToString(TokenType const &type) -> std::string {
  switch(type) {
    case tidakDiketahui:
      return "tidak diketahui";
    case ruangKosong:
      return "ruang kosong";
    case barisBaru:
      return "baris baru";
    case akhirDariFile:
      return "akhir dari file";
    case identifikasi:
      return "identifikasi";
    case kurungBulatBuka:
      return "kurung bulat buka";
    case kurungBulatTutup:
      return "kurung bulat tutup";
    case titikKoma:
      return "titik koma";
    default:
      std::cerr << "Tipe token tidak dapat diubah ke string." << "\n";
      break;
  }
}

void lexer::createToken(
  const std::string& fileName, 
  const size_t& row,
  size_t& column, 
  const std::smatch& matches,
  const TokenType& tokenType, 
  std::string& content,
  Token& token
) {
  std::string contentTemp = matches.str();

  token.fileName = fileName;
  token.location.row = row;
  token.location.column = column;
  token.content = std::move(contentTemp);
  token.type = tokenType;

  column += matches.length();

  content.erase(matches.position(), matches.length());
}

void lexer::muatFile(std::string const &path, std::string &content) {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Gagal membuka file: " << path << "\n";
  }

  file.seekg(0, std::ios::end);
  content.resize(file.tellg());
  file.seekg(0, std::ios::beg);

  file.read(content.data(), static_cast<std::streamsize>(content.size()));

  file.close();
}

void lexer::generateToken(
  const std::string& fileName, 
  TokenLocation& location,
  std::string& content, 
  Token& token
) {
  std::smatch matches;

  for (const TokenRegex &tokenRegex : tokenRegexs()) {
    if(std::regex_search(content, matches, tokenRegex.getRegex())) {
      createToken(
        fileName,
        location.row, 
        location.column, 
        matches,
        tokenRegex.getType(), 
        content, 
        token
      );

      if(tokenRegex.getType() == TokenType::barisBaru) {
        location.row++;
        location.column = 1;
      }

      break;
    }
  }
}

void lexer::generateTokens(
  std::string const &fileName, 
  TokenLocation &location,
  std::string &content, 
  std::vector<Token> &tokens
) {
  while (content.size() > 0) {
    Token token;
    generateToken(fileName, location, content, token);
    if(
      token.type != TokenType::ruangKosong &&
      token.type != TokenType::barisBaru &&
      token.type != TokenType::tidakDiketahui
    ) {
      tokens.push_back(std::move(token));
    }
  }

  tokens.push_back(
    {
      fileName,
      {
        location.row, 
        location.column - location.row + 1
      },
      TokenType::akhirDariFile,
      ""
    }
  );
}