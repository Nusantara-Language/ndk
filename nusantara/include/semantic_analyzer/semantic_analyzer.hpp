#pragma once

// Include STD C++

// Include library file
#include "parser/parser.hpp"

namespace nusantara {

  // Class
  class SemanticAnalyzer {
    public:
      // Fungsi
      static auto analyze(const nusantara::Node& node) -> bool;

    private:
      // Fungsi
      static auto analyzeToken(const nusantara::Node& node) -> bool;
      static auto analyzeFunctionCall(const nusantara::Node& node) -> bool;
      static auto analyzeAwal(const nusantara::Node& node) -> bool;
      static auto analyzePernyataanEkspresi(const nusantara::Node& node) -> bool;
      static auto analyzeTempatParameterPanggilFungsi(const nusantara::Node& node) -> bool;
  };

} // namespace nusantara