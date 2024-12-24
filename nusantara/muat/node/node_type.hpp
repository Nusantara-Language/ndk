#pragma once

#include <string>

// Namespace
namespace nusantara {

  // Enum
  enum NodeType {
    TOKEN,
    AWAL,
    PERNYATAAN_EKSPRESI,
    PANGGIL_FUNGSI,
    TEMPAT_PARAMETER_PANGGIL_FUNGSI,
  };

  // Function
  auto nodeTypeToString(const NodeType &type) -> std::string;

}  // namespace nusantara
