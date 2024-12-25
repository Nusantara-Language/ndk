/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "kawasan/kawasan.hpp"
#include <any>

namespace nusantara {

  class LingkunganEksekusi {
    public:
      LingkunganEksekusi();

      Kawasan& ambilKawasan();

      std::any ambilDataSementara();
      
      void aturDataSementara(std::any nilai);

      void hapusDataSementara();
    // akhir dari access modifiers public

    private:
      std::any dataSementara;
      Kawasan kawasan;
    // akhir dari access modifiers private

  }; // class Runtime

} // namespace nusantara