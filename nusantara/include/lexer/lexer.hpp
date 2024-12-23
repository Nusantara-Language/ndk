#pragma once

#include "token/token_regex.hpp"

#include "token/token.hpp"

#include "token/token_type.hpp"

#include <regex>

#include <set>

#include <string>

// Namespace
namespace nusantara 
{

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
