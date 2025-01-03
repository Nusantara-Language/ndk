/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef CETAK_HPP
#define CETAK_HPP

#include <format>
#include <iostream>

#include "catatan/catatan.ap.hpp"
#include "cetak/apakah_bisa_di_cetak_ke_konsol.hpp"
#include "konfig/konfig_label_keluaran.hpp"

namespace nusantara {

template <typename Type>
void cetak(const Type& nilai)
{
  if (ApakahBisaDiCetakKeKonsol<Type>())
  {
    std::cout << nilai;
  }
  else
  {
    __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Fungsi Cetak"), "Tipe data ", typeid(Type).name(),
        " tidak dapat dicetak ke konsol.\n"); // __CATATAN__KESALAHAN_FATAL_M__
  } // else
} // function cetak

template <typename... Types>
void cetak(const Types&... kumpulanNilai)
{
  (cetak(kumpulanNilai), ...);
} // function cetak

template <typename... Types>
void cetakDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai)
{
  cetak(std::vformat(formatString.get(), std::make_format_args(kumpulanNilai...)));
} // function cetakDF

template <typename Type>
void cetakDBB(const Type& nilai)
{
  cetak(nilai);
  std::cout << "\n";
} // function cetakDBB

template <typename... Types>
void cetakDBB(const Types&... kumpulanNilai)
{
  (cetak(kumpulanNilai), ...);
  std::cout << "\n";
} // function cetakDBB

template <typename... Types>
void cetakDBBDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai)
{
  cetakDF(formatString, kumpulanNilai...);
  std::cout << "\n";
} // function cetakDBBDF

} // namespace nusantara

#endif
