#pragma once

#include <string>

#include "token/token_type.hpp"

// Namespace
namespace nusantara 
{

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
    std::string content;
  };

}  // namespace nusantara