/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "lingkungan_eksekusi/kawasan/kawasan.hpp"
#include "a_fungsi.hpp"
#include <string>

namespace nusantara {

  class Fungsi: public AFungsi {
    public:
      Fungsi(const std::string& nama);
      
      Fungsi(const std::string& nama, Kawasan&& kawasan);

      void panggil() override;

      const std::string& ambilNama() override;
    // akhir dari access modifiers public

    private:
      std::string nama;
    // akhir dari access modifiers private

    protected:
      Kawasan kawasan;
    // akhir dari access modifiers protected

  }; // class Fungsi

} // namespace nusantara