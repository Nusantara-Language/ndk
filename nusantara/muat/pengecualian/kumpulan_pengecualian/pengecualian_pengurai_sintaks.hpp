/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <stdexcept>
#include <string>

namespace nusantara {

  struct PengecualianPenguraiSintaks : public std::runtime_error {
    explicit PengecualianPenguraiSintaks(const std::string& pesan): std::runtime_error(pesan) {}
  }; // struct PengecualianPenguraiSintaks

}// namespace nusantara