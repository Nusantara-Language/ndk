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

  enum TipeToken {
    kurungBulatBuka,
    kurungBulatTutup,
    barisBaru,
    ruangKosong,
    titikKoma,
    bilangan,
    identifikasi,
    tidakDiketahui,
    akhirDariFile,
  }; // enum TipeToken

  auto tipeTokenKeString(const TipeToken& type) -> std::string;

} // namespace nusantara