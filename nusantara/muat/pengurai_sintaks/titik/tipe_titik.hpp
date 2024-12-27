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

namespace nusantara {

  enum TipeTitik {
    TOKEN,
    AWAL,
    PERNYATAAN_EKSPRESI,
    PANGGIL_FUNGSI,
    TEMPAT_PARAMETER_PANGGIL_FUNGSI,
    AKHIR_DARI_FILE,
    BILANGAN,
  }; // enum TipeTitik

  auto tipeTitikKeString(const TipeTitik &tipe) -> std::string;

} // namespace nusantara