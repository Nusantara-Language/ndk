/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "blok_kode/blok_kode.hpp"
#include <any>

namespace nusantara {

  class LingkunganEksekusi {
    public:
      LingkunganEksekusi();

      BlokKode& ambilBlokKode();

      std::any ambilDataSementara();
      
      void aturDataSementara(std::any nilai);

      void hapusDataSementara();
    // akhir dari access modifiers public

    private:
      std::any dataSementara;
      BlokKode blokKode;
    // akhir dari access modifiers private

  }; // class Runtime

} // namespace nusantara