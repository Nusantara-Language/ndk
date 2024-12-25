/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

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
  }; // struct Token

} // namespace nusantara