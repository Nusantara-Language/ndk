/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifdef CATATAN

#pragma once

#include <string>

namespace nstd {

  class Catatan {
    public:
      static void info(const std::string& pesan);
      static void kesalahan(const std::string& pesan);
      static void peringatan(const std::string& pesan);
    // akhir dari access modifiers public
  
    private:
      #ifdef CATATAN_SIMPAN_BERKAS
        Catatan();
        ~Catatan();

        Catatan(const Catatan&) = delete;
        Catatan& operator=(const Catatan&) = delete;

        static Catatan* instance;

        std::string lokasiFolder;
        std::string namaBerkas;
        std::string lokasiBerkas;

        static Catatan* ambilInstance();
      #endif
    // akhir dari access modifiers private
  
  }; // class Catatan

} // namespace nstd

#endif