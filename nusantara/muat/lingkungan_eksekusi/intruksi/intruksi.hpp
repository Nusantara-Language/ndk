/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

namespace nusantara {

  class Intruksi {
    public:
      virtual ~Intruksi() = default;

      virtual void jalankan() = 0;
    // akhir dari access modifiers public

  }; // class Intruksi

} // namespace nusantara