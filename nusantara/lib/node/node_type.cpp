#include "node/node_type.hpp"
#include <iostream>

auto nusantara::nodeTypeToString(const NodeType &type) -> std::string {
  switch(type) {
    case AWAL:
      return "AWAL";
    case PERNYATAAN_EKSPRESI:
      return "PERNYATAAN EKSPRESI";
    case PANGGIL_FUNGSI:
      return "PANGGIL FUNGSI";
    case TEMPAT_PARAMETER_PANGGIL_FUNGSI:
      return "TEMPAT PARAMETER PANGGIL FUNGSI";
    case TOKEN:
      return "TOKEN";
    default:
      std::cerr << "Invalid Node type!" << '\n';
      break;
  }
}