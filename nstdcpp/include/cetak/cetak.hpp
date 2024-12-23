#pragma once

#include <format>
#include <iostream>
#include <type_traits>

namespace nstd {

  // Struktur untuk menentukan apakah tipe T bisa dicetak ke std::cout
  template <typename T, typename = void>
  struct CanOutput : std::false_type {};

  // Spesialisasi untuk tipe yang dapat dicetak ke std::cout
  template <typename T>
  struct CanOutput<T, std::void_t<decltype(std::cout << std::declval<T>())>> : std::true_type {};

  // Fungsi cetak untuk tipe yang dapat dicetak ke std::cout
  template<typename Type>
  void cetak(const Type& nilai) {
    if constexpr (CanOutput<Type>()) {
      std::cout << nilai;
    } else {
      std::cerr << "Tipe data " << typeid(Type).name() << " tidak dapat dicetak.\n";
    }
  }

  // Fungsi cetak untuk banyak nilai sekaligus
  template<typename... Types>
  void cetak(const Types&... kumpulanNilai) {
    (cetak(kumpulanNilai), ...);  // Menggunakan fold expression untuk pemanggilan fungsi cetak secara rekursif
  }

  // Fungsi cetak dengan format string dan argumen tambahan
  template<typename... Types>
  void cetakDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    cetak(std::vformat(formatString.get(), std::make_format_args(kumpulanNilai...)));
  }

  // Fungsi cetak dengan baris baru (termasuk penambahan "\n")
  template<typename Type>
  void cetakDBB(const Type& nilai) {
    cetak(nilai);
    std::cout << "\n";
  }

  // Fungsi cetak banyak nilai sekaligus dengan baris baru
  template<typename... Types>
  void cetakDBB(const Types&... kumpulanNilai) {
    (cetak(kumpulanNilai), ...);  // Pemanggilan cetak untuk setiap nilai
    std::cout << "\n";
  }

  // Fungsi cetak dengan format dan baris baru
  template<typename... Types>
  void cetakDBBDF(const std::format_string<Types...>& formatString, const Types&... kumpulanNilai) {
    cetakDF(formatString, kumpulanNilai...);
    std::cout << "\n";
  }

} // namespace nstd