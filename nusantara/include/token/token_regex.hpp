#pragma once

#include <regex>
#include <utility>

#include "token/token_type.hpp"

// Namespace
namespace nusantara 
{

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

}  // namespace nusantara