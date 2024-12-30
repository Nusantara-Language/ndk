/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef TIPE_TOKEN_HPP
#define TIPE_TOKEN_HPP

#include <string>

namespace nusantara {

enum TipeToken
{
  kurungBulatBuka,
  kurungBulatTutup,
  barisBaru,
  ruangKosong,
  muat,
  titikKoma,
  nilaiBilangan,
  nilaiTeks,
  identifikasi,
  tidakDiketahui,
  akhirDariFile,
}; // enum TipeToken

auto tipeTokenKeString(const TipeToken& type) -> std::string;

} // namespace nusantara

#endif
