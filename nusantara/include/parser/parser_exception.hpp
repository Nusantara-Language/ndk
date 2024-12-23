#pragma once

#include <stdexcept>
#include <string>

// Namespace
namespace nusantara {
  // Struct
  struct ParserException : public std::runtime_error {
    // Constructor
    explicit ParserException(
      const std::string &message
    ): 
    std::runtime_error(message) 
    {}
  };
  
}  // namespace nusantara