/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language",
 * Penulis: Fern Aerell",
 * Lisensi: BSD 3-Clause License",
 * Hak Cipta (c) 2024, Nusantara",
 * ----------------------------------------------------------------------------
 */

#ifndef APAKAH_BISA_DI_CETAK_KE_KONSOL_HPP
#define APAKAH_BISA_DI_CETAK_KE_KONSOL_HPP

#include <type_traits>
#include <iostream>

namespace nusantara {

  template <typename T, typename = void>
  struct ApakahBisaDiCetakKeKonsol : public std::false_type {
    static constexpr bool value = false;
  }; // struct BisaDiCetak

  template <typename T>
  struct ApakahBisaDiCetakKeKonsol<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

} // namespace nusantara

#endif
