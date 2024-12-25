/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <functional>
#include <cstddef>
#include <string>
#include <vector>
#include <regex>

namespace nusantara {

  class EksekusiPerintah;

  class Perintah {
    public:
      Perintah(
        std::string nama,
        std::string deskripsi,
        std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi,
        const bool &tanpaArgumen
      );

      Perintah(
        std::regex regex,
        std::string name,
        std::string description,
        std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi,
        const bool &tanpaArgumen
      );

      [[nodiscard]] const std::string& ambilNama() const;

      [[nodiscard]] const std::string& ambilDeskripsi() const;

      [[nodiscard]] const std::regex& ambilRegex() const;

      [[nodiscard]] std::string ubahKeString() const;

      void eksekusi(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &argumen);

      bool operator==(const Perintah& other);
    // akhir dari access modifiers public

    private:
      bool tanpaArgumen;

      std::function<void(EksekusiPerintah &, size_t &, std::vector<std::string> &)> intruksi;

      std::string nama;

      std::string deskripsi;

      std::regex regex;
    // akhir dari access modifiers private

    protected:
    // akhir dari access modifiers protected

  }; // class Perintah

  class EksekusiPerintah {
    public:
      EksekusiPerintah() = default;

      void tambah(Perintah argumen);

      const std::vector<Perintah>& ambilKumpulanPerintah();

      void eksekusi(std::vector<std::string> argumen);
    // akhir dari access modifiers public

    private:
      std::vector<Perintah> kumpulanPerintah;
    // akhir dari access modifiers private

  }; // class EksekusiPerintah

} // namespace nusantara