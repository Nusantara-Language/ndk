#pragma once

#include <chrono>

namespace nstd {

  class WaktuEksekusi {
    public:
      static void mulai();
      static void selesai();
      static void cetak();
    private:
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuMulai; // NOLINT
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuSelesai; // NOLINT
  };

} // namespace nstd