/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "lingkungan_eksekusi/intruksi/kumpulan_intruksi.hpp"
#include "lingkungan_eksekusi/fungsi/kumpulan_fungsi.hpp"

namespace nusantara {

  class Kawasan {
    public:
      Kawasan(
        KumpulanFungsi &&kumpulanFungsi,
        KumpulanIntruksi &&kumpulanIntruksi
      );

      KumpulanIntruksi& ambilKumpulanIntruksi();
      
      KumpulanFungsi& ambilKumpulanFungsi();
    // akhir dari access modifiers public

    private:
      KumpulanIntruksi kumpulanIntruksi;
      KumpulanFungsi kumpulanFungsi;
    // akhir dari access modifiers private

  }; // class Kawasan

} // namespace nusantara