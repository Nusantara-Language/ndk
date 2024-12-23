#pragma once

// Include STD C++
#include <string>

#include <memory>

#include "node/node.hpp"

namespace nusantara {

  // Class
  class Interpreter {
    public:
      // Fungsi
      static auto interpretation(const std::unique_ptr<nusantara::Node> &node) -> void;

    private:
      // Fungsi
      static auto interpretToken(const nusantara::Node& node) -> std::string;
      static auto interpretFunctionCall(const nusantara::Node& node) -> void;
      static auto interpretAwal(const nusantara::Node& node) -> void;
      static auto interpretPernyataanEkspresi(const nusantara::Node& node) -> void;
      static auto interpretTempatParameterPanggilFungsi(const nusantara::Node& node) -> void;
  };

} // namespace nusantara