/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <format>
#include <string>

#include "token/tipe_token.hpp"

namespace nusantara {

  struct LokasiToken {
    size_t baris;    
    size_t kolom;
  }; // struct LokasiToken

  struct Token {
    std::string lokasiBerkas;
    LokasiToken lokasi;
    TipeToken tipe;
    std::string konten;

    std::string ubahKeString() const {
      return  std::format("{}:{}:{} [{}] {}", this->lokasiBerkas, this->lokasi.baris, this->lokasi.kolom, tipeTokenKeString(this->tipe), this->konten);
    }

    friend std::ostream& operator<<(std::ostream& os, const Token& token) {
      os << token.ubahKeString();
      return os;
    }
  }; // struct Token

} // namespace nusantara