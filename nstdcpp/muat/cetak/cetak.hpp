/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <iostream>
#include <format>

#include "cetak/apakah_bisa_di_cetak_ke_konsol.hpp"

namespace nstd {

  template<typename Type>
  void cetak(const Type& nilai) {
    if (ApakahBisaDiCetakKeKonsol<Type>()) {
      std::cout << nilai;
    } else {
      std::cerr << "[FUNGSI CETAK] Tipe data " << typeid(Type).name() << " tidak dapat dicetak ke konsol.\n";
    }
  }  // function cetak

  template<typename... Types>
  void cetak(const Types&... kumpulanNilai) {
    (cetak(kumpulanNilai), ...);
  }  // function cetak

  template<typename... Types>
  void cetakDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    cetak(std::vformat(formatString.get(), std::make_format_args(kumpulanNilai...)));
  }  // function cetakDF

  template<typename Type>
  void cetakDBB(const Type& nilai) {
    cetak(nilai);
    std::cout << "\n";
  } // function cetakDBB

  template<typename... Types>
  void cetakDBB(const Types&... kumpulanNilai) {
    (cetak(kumpulanNilai), ...);
    std::cout << "\n";
  } // function cetakDBB 

  template<typename... Types>
  void cetakDBBDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    cetakDF(formatString, kumpulanNilai...);
    std::cout << "\n";
  } // function cetakDBBDF

} // namespace nstd