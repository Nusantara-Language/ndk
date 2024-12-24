/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

// Blokir pengulangan header
#pragma once


#include <iostream>
#include <format>


#include "cetak/bisa_di_cetak.hpp"


namespace nstd {

  /**
   * Fungsi cetak untuk tipe yang dapat dicetak ke std::cout.
   *
   * @tparam Type Jenis data yang ingin dicetak.
   *
   * @param nilai Nilai yang ingin dicetak.
   */
  template<typename Type>
  void cetak(const Type& nilai) {
    // Periksa apakah nilai tersebut dapat dicetak
    if (BisaDiCetak<Type>()) {
      // Jika dapat, tuliskan nilainya ke std::cout
      std::cout << nilai;
    } else {
      // Jika tidak dapat, tampilkan pesan kesal
      std::cerr << "Tipe data " << typeid(Type).name() << " tidak dapat dicetak.\n";
    }
  }

  /**
   * Fungsi cetak untuk banyak nilai sekaligus.
   *
   * @tparam Types Jenis-jenis data yang ingin dicetak.
   * @param kumpulanNilai Kumpulan nilai yang ingin dicetak.
   */
  template<typename... Types>
  void cetak(const Types&... kumpulanNilai) {
    /**
     * Menggunakan fold expression untuk pemanggilan fungsi cetak secara rekursif.
     * Fungsi ini akan memanggil dirinya sendiri untuk setiap argumen dalam parameter list.
     */
    (cetak(kumpulanNilai), ...);
  }

  /**
   * Fungsi cetak dengan format string dan argumen tambahan.
   *
   * @tparam Types Jenis-jenis data yang ingin dicetak.
   * @param formatString Format string yang akan digunakan untuk mencetak nilai.
   * @param kumpulanNilai Kumpulan nilai yang ingin dicetak.
   */
  template<typename... Types>
  void cetakDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    /**
     * Menggunakan vformat untuk mencetak nilai sesuai dengan format string.
     */
    cetak(std::vformat(formatString.get(), std::make_format_args(kumpulanNilai...)));
  }

  /**
   * Fungsi cetak dengan baris baru (termasuk penambahan "\n")
   *
   * @tparam Type Jenis data yang ingin dicetak.
   * @param nilai Nilai yang ingin dicetak.
   */
  template<typename Type>
  void cetakDBB(const Type& nilai) {
    /**
     * Fungsi ini memanggil fungsi cetak dengan parameter biasa, kemudian menambahkan baris baru
     * untuk memisahkan antara hasil cetakan dan teks lain.
     */
    cetak(nilai);
    std::cout << "\n";
  }

  /**
   * Fungsi cetak banyak nilai sekaligus dengan baris baru.
   *
   * @tparam Types Jenis-jenis data yang ingin dicetak.
   * @param kumpulanNilai Kumpulan nilai yang ingin dicetak.
   */
  template<typename... Types>
  void cetakDBB(const Types&... kumpulanNilai) {
    /**
     * Pemanggilan fungsi cetak untuk setiap nilai dalam parameter list,
     * kemudian ditambahkan baris baru untuk memisahkan hasil cetakan.
     */
    (cetak(kumpulanNilai), ...);
    std::cout << "\n";
  }

  /**
   * Fungsi cetak dengan format string dan baris baru.
   *
   * @tparam Types Jenis-jenis data yang ingin dicetak.
   * @param formatString Format string yang akan digunakan untuk mencetak nilai.
   * @param kumpulanNilai Kumpulan nilai yang ingin dicetak.
   */
  template<typename... Types>
  void cetakDBBDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    /**
     * Fungsi ini memanggil fungsi cetak dengan format string,
     * kemudian ditambahkan baris baru untuk memisahkan hasil cetakan.
     */
    cetakDF(formatString, kumpulanNilai...);
    std::cout << "\n";
  }

} // namespace nstd