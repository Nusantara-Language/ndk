#pragma once

#include <cstddef>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

namespace lexer {

enum TokenType {
  kurungBulatBuka,
  kurungBulatTutup,
  kurungKurawalBuka,
  kurungKurawalTutup,
  barisBaru,
  ruangKosong,
  fungsi,
  identifikasi,
  tidakDiketahui,
  akhirDariFile,
};

struct TokenLocation {
  size_t row;
  size_t column;
};

struct Token {
  std::string fileName;
  TokenLocation location;
  TokenType type;
  std::string content;
};

class TokenRegex {
public:
  TokenRegex(std::regex regex, const TokenType &type)
      : regex(std::move(regex)), type(type) {}
  auto operator<(const TokenRegex &other) const -> bool;
  auto operator>(const TokenRegex &other) const -> bool;
  [[nodiscard]] auto getRegex() const -> const std::regex &;
  [[nodiscard]] auto getType() const -> const TokenType &;

private:
  std::regex regex;
  TokenType type = TokenType::tidakDiketahui;
};

auto tokenRegexs() -> const std::set<lexer::TokenRegex> &;

auto tokenTypeToString(const TokenType &type) -> std::string;

void muatFile(const std::string &path, std::string &content);

void createToken(const std::string &fileName, const size_t &row, size_t &column,
                 const std::smatch &matches, const TokenType &tokenType,
                 std::string &content, Token &token);

void generateToken(std::string const &fileName, TokenLocation &location,
                   std::string &content, Token &token);

void generateTokens(std::string const &fileName, TokenLocation &location,
                    std::string &content, std::vector<Token> &tokens);

} // namespace lexer
