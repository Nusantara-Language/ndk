#pragma once

// Include STD C++
#include <cstddef>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

// Namespace
namespace nusantara 
{
  enum TokenType 
  {
    kurungBulatBuka,
    kurungBulatTutup,
    barisBaru,
    ruangKosong,
    titikKoma,
    identifikasi,
    tidakDiketahui,
    akhirDariFile,
  };

  struct TokenLocation 
  {
    size_t row;
    size_t column;
  };

  struct Token 
  {
    std::string filePath;
    TokenLocation location;
    TokenType type;
    std::string content;  // Menggunakan string_view
  };

  class TokenRegex 
  {
    public:
      TokenRegex(std::regex regex, const TokenType& type)
        : regex(std::move(regex)), type(type) {}

      [[nodiscard]] auto getRegex() const -> const std::regex& { return regex; }
      [[nodiscard]] auto getType() const -> const TokenType& { return type; }

      auto operator<(const TokenRegex& other) const -> bool { return type < other.type; }
      auto operator>(const TokenRegex& other) const -> bool { return type > other.type; }

    private:
      std::regex regex;
      TokenType type;
  };

  auto nTokenRegexs() -> const std::set<TokenRegex>&;

  auto tokenTypeToString(const TokenType& type) -> std::string;

  class Lexer 
  {
    public:
      explicit Lexer(std::set<TokenRegex> tokenRegexs)
        : tokenRegexs(std::move(tokenRegexs)), tokenLocation({1, 1}) {}

      auto read(std::string filepath) -> bool;
      auto tokenization() -> void;
      [[nodiscard]] auto getResult() const -> const std::vector<Token>&;
      auto print() -> void;

    private:
      std::string filepath;
      std::string content;

      std::set<TokenRegex> tokenRegexs;
      std::vector<Token> tokenizationResult;

      TokenLocation tokenLocation;

      auto generateToken(Token& token) -> void;
      auto generateTokens() -> void;
      auto createToken(const std::smatch& matches, const TokenType& tokenType, Token& token) -> void;
  };
}  // namespace nusantara
