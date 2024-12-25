/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language",
 * Penulis: Fern Aerell",
 * Lisensi: BSD 3-Clause License",
 * Hak Cipta (c) 2024, Nusantara",
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <type_traits>
#include <iostream>

namespace nstd {

  template <typename T, typename = void>
  struct ApakahBisaDiCetakKeKonsol : public std::false_type {
    static constexpr bool value = false;
  }; // struct BisaDiCetak

  template <typename T>
  struct ApakahBisaDiCetakKeKonsol<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

} // namespace nstd