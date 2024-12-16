#include "lexer.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

std::vector<Lexer::TokenRegex> token_regexs = {
    Lexer::TokenRegex{
        std::regex("^[(]"), 
        Lexer::TokenType::KURUNG_BULAT_BUKA
    },
    Lexer::TokenRegex{
        std::regex("^[)]"), 
        Lexer::TokenType::KURUNG_BULAT_TUTUP
    },
    Lexer::TokenRegex{
        std::regex("^[{]"), 
        Lexer::TokenType::KURUNG_KURAWAL_BUKA
    },
    Lexer::TokenRegex{
        std::regex("^[}]"), 
        Lexer::TokenType::KURUNG_KURAWAL_TUTUP
    },
    Lexer::TokenRegex{
        std::regex("^[\n]"), 
        Lexer::TokenType::BARIS_BARU
    },
    Lexer::TokenRegex{
        std::regex("^\\s"), 
        Lexer::TokenType::RUANG_KOSONG
    },
    Lexer::TokenRegex{
        std::regex("^fungsi"), 
        Lexer::TokenType::FUNGSI
    },
    Lexer::TokenRegex{
        std::regex("^[a-zA-Z][a-zA-Z0-9_]*"), 
        Lexer::TokenType::IDENTIFIKASI
    },
    Lexer::TokenRegex{
        std::regex("^."), 
        Lexer::TokenType::TIDAK_DIKETAHUI
    },
};

std::string Lexer::tokenTypeToString(TokenType const &type) {
  switch (type) {
  case TIDAK_DIKETAHUI:
    return "tidak diketahui";
  case RUANG_KOSONG:
    return "ruang kosong";
  case BARIS_BARU:
    return "baris baru";
  case AKHIR_DARI_FILE:
    return "akhir dari file";
  case IDENTIFIKASI:
    return "identifikasi";
  case KURUNG_KURAWAL_BUKA:
    return "kurung kurawal buka";
  case KURUNG_KURAWAL_TUTUP:
    return "kurung kurawal tutup";
  case KURUNG_BULAT_BUKA:
    return "kurung bulat buka";
  case KURUNG_BULAT_TUTUP:
    return "kurung bulat tutup";
  case FUNGSI:
    return "fungsi";
  default:
    std::cerr << "Invalid token type" << "\n";
    exit(1);
    break;
  }
}

void Lexer::createToken(std::string const &filename, int const &row, int &column,
                         std::smatch const &matches,
                         TokenType const &TokenType, std::string &content,
                         Token &token) {
  std::string contentTemp = matches.str();

  token.fileName = filename;
  token.row = row;
  token.column = column;
  token.content = std::move(contentTemp);
  token.type = TokenType;

  column += matches.length();

  content.erase(matches.position(), matches.length());
}

void Lexer::muatFile(std::string const &path, std::string &content) {
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Gagal membuka file: " << path << "\n";
    exit(1);
  }

  file.seekg(0, std::ios::end);
  content.resize(file.tellg());
  file.seekg(0, std::ios::beg);
  file.read(&content[0], content.size());
  file.close();
}

void Lexer::generateToken(std::string const &filename, int &row, int &column,
                           std::string &content, Token &token) {
  std::smatch matches;

  for(int i = 0; i < token_regexs.size(); ++i)
  {
    if(std::regex_search(content, matches, token_regexs[i].regex))
    {
        createToken(filename, row, column, matches, token_regexs[i].type, content, token);
        if(token_regexs[i].type == TokenType::BARIS_BARU) {
            row++;
            column = 1;
        }
        break;
    }
  }
}

void Lexer::generateTokens(std::string const &filename, int &row, int &column,
                            std::string &content, std::vector<Token> &tokens) {
  while (content.size() > 0) {
    Token token;
    generateToken(filename, row, column, content, token);
    if(
      token.type != TokenType::RUANG_KOSONG &&
      token.type != TokenType::BARIS_BARU &&
      token.type != TokenType::TIDAK_DIKETAHUI
    ) {
      tokens.push_back(std::move(token));
    }
  }
  tokens.push_back({
    filename,
    row,
    column - row + 1,
    TokenType::AKHIR_DARI_FILE,
    "\0"
  });
}