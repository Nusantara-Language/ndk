/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <chrono>

#include "waktu_eksekusi/waktu_eksekusi.hpp"
#include "cetak/cetak.hpp"

std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuMulai;  // NOLINT

std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuSelesai;  // NOLINT

void nstd::WaktuEksekusi::mulai() {
  nstd::WaktuEksekusi::waktuMulai = std::chrono::high_resolution_clock::now();
} // function nstd::WaktuEksekusi::mulai

void nstd::WaktuEksekusi::selesai() {
 nstd::WaktuEksekusi::waktuSelesai = std::chrono::high_resolution_clock::now();
} // function nstd::WaktuEksekusi::selesai

void nstd::WaktuEksekusi::cetak() {
  auto waktuSelesai = std::chrono::high_resolution_clock::now();

  auto durasiWaktuEksekusi = std::chrono::duration_cast<std::chrono::microseconds>(waktuSelesai - nstd::WaktuEksekusi::waktuMulai).count();

  auto durasiDalamJam = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL * 60LL);

  durasiWaktuEksekusi %= (1000LL * 1000LL * 60LL * 60LL);

  auto durasiDalamMenit = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL);

  auto durasiDalamDetik = durasiWaktuEksekusi / (1000LL * 1000LL);

  auto durasiDalamMiliDetik = durasiWaktuEksekusi / 1000LL;

  auto durasiDalamMicroDetik = durasiWaktuEksekusi % 1000LL;

  nstd::cetakDF(
    "\nDurasi waktu eksekusi: {} jam, {} menit, {} detik, {} milidetik, {} microdetik", 
    durasiDalamJam, 
    durasiDalamMenit, 
    durasiDalamDetik, 
    durasiDalamMiliDetik, 
    durasiDalamMicroDetik
  ); // function nstd::cetakDF

} // function nstd::WaktuEksekusi::cetak