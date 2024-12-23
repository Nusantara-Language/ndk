#include "waktu_eksekusi/waktu_eksekusi.hpp"
#include "cetak/cetak.hpp"
#include <chrono>

std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuMulai; // NOLINT
std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuSelesai;  // NOLINT

void nstd::WaktuEksekusi::mulai() {
  nstd::WaktuEksekusi::waktuMulai = std::chrono::high_resolution_clock::now();
}

void nstd::WaktuEksekusi::selesai() {
  nstd::WaktuEksekusi::waktuSelesai = std::chrono::high_resolution_clock::now();
}

void nstd::WaktuEksekusi::cetak() {
  auto waktuSelesai = std::chrono::high_resolution_clock::now();
  auto durasiWaktuEksekusi = std::chrono::duration_cast<std::chrono::microseconds>(nstd::WaktuEksekusi::waktuSelesai - nstd::WaktuEksekusi::waktuMulai).count();

  auto durasiDalamJam = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL * 60LL); // NOLINT
  durasiWaktuEksekusi %= (1000LL * 1000LL * 60LL * 60LL); // NOLINT

  auto durasiDalamMenit = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL); // NOLINT
  durasiWaktuEksekusi %= (1000LL * 1000LL * 60LL); // NOLINT

  auto durasiDalamDetik = durasiWaktuEksekusi / (1000LL * 1000LL); // NOLINT
  durasiWaktuEksekusi %= (1000LL * 1000LL); // NOLINT

  auto durasiDalamMiliDetik = durasiWaktuEksekusi / 1000LL; // NOLINT
  auto durasiDalamMicroDetik = durasiWaktuEksekusi % 1000LL; // NOLINT

  nstd::cetakDF(
    "\nDurasi waktu eksekusi: {} jam, {} menit, {} detik, {} milidetik, {} microdetik", 
    durasiDalamJam, 
    durasiDalamMenit, 
    durasiDalamDetik, 
    durasiDalamMiliDetik, 
    durasiDalamMicroDetik
  );
}