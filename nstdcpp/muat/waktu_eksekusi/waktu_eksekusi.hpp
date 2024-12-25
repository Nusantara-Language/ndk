/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <chrono>

namespace nstd {

  class WaktuEksekusi {
    public:
      static void mulai();
      
      static void selesai();
      
      static void cetak();
    // akhir dari access modifiers public
  
    private:
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuMulai; // NOLINT
      
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuSelesai; // NOLINT
    // akhir dari access modifiers private

    protected:
    // akhir dari access modifiers protected

  }; // class WaktuEksekusi

} // namespace nstd