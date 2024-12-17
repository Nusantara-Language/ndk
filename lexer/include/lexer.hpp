// Header guard
#ifndef LEXER_HPP
#define LEXER_HPP

// Include STD C++
#include <cstddef>
#include <regex>
#include <set>
#include <string>
#include <utility>
#include <vector>

// Namespace
namespace lexer 
{

  // Enum
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

  // Struct
  struct TokenLocation 
  {
    size_t row;
    size_t column;
  };

  struct Token 
  {
    std::string fileName;
    TokenLocation location;
    TokenType type;
    std::string content;
  };

  // Class
  class TokenRegex 
  {
    public:
      // Constructor
      TokenRegex(
        std::regex regex, 
        const TokenType& type
      ): 
      regex(std::move(regex)), 
      type(type)
      {}

      // Class Getter
      [[nodiscard]] auto getRegex() const -> const std::regex&;
      [[nodiscard]] auto getType() const -> const TokenType&;

      // Class Operator
      auto operator<(const TokenRegex& other) const -> bool;
      auto operator>(const TokenRegex& other) const -> bool;

    private:
      // Variable
      std::regex regex;
      TokenType type = TokenType::tidakDiketahui;
  };

  // Function
  auto tokenRegexs() -> const std::set<lexer::TokenRegex>&;

  auto tokenTypeToString(const TokenType& type) -> std::string;

  void muatFile(
    const std::string& path, 
    std::string& content
  );

  void createToken(
    const std::string& fileName,
    const size_t& row,
    size_t& column,
    const std::smatch& matches,
    const TokenType& tokenType,
    std::string& content,
    Token& token
  );

  void generateToken(
    std::string const& fileName,
    TokenLocation& location,
    std::string& content,
    Token& token
  );

  void generateTokens(
    std::string const& fileName,
    TokenLocation& location,
    std::string& content,
    std::vector<Token>& tokens
  );

}  // namespace lexer

#endif
