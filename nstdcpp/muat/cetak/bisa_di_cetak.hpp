/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language",
 * Penulis: Fern Aerell",
 * Lisensi: BSD 3-Clause License",
 * Hak Cipta (c) 2024, Nusantara",
 * ----------------------------------------------------------------------------
 */

// Blokir pengulangan header
#pragma once


#include <type_traits>
#include <iostream>


namespace nstd {

  /**
   * @brief Struktur untuk menentukan apakah tipe T bisa dicetak ke std::cout.
   *
   * @tparam T Tipe data yang ingin diuji.
   */
  template <typename T, typename = void>
  struct BisaDiCetak : public std::false_type {
    /**
     * @brief Kondisi untuk menguji apakah tipe T bisa dicetak ke std::cout.
     *
     * Jika kondisi ini dijalankan dengan sukses, maka struktur akan menjadi std::true_type.
     */
    static constexpr bool value = false;
  };

  /**
   * @brief Template untuk memeriksa apakah tipe T dapat dicetak ke std::cout.
   *
   * @param T Tipe data yang ingin diuji.
   *
   * @return true jika tipe T dapat dicetak ke std::cout, false jika tidak.
   */
  template <typename T>
  struct BisaDiCetak<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {
    /**
     * @brief Menggunakan SFINAE (Substitution Failure Is Not An Error) untuk memeriksa apakah tipe T dapat dicetak ke std::cout.
     */
    /**
     * @brief Penggunaan `decltype` untuk mendapatkan jenis data yang dihasilkan dari ekspresi `std::cout << std::declval<T>()`.
     *
     * Jika hasilnya adalah `void`, maka tipe T tidak dapat dicetak ke std::cout.
     */
    /**
     * @brief Penggunaan `std::void_t` untuk membuat template metode yang dapat diuji apakah tipe T dapat dicetak ke std::cout.
     *
     * Dengan menggunakan `std::void_t`, kita dapat menghilangkan warna error jika tidak ada kondisi untuk memeriksa apakah tipe T dapat dicetak ke std::cout.
     */
    /**
     * @brief Penggunaan `std::declval` untuk mendapatkan objek yang tidak pernah digunakan dalam ekspresi, sehingga kita dapat menguji apakah tipe T dapat dicetak ke std::cout.
     *
     * Dengan menggunakan `std::declval`, kita dapat memastikan bahwa tipe T hanya diuji pada kondisi yang tepat.
     */
  };

}// nstd