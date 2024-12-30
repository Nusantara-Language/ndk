/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <chrono>

#include "cetak/cetak.hpp"
#include "waktu_eksekusi/waktu_eksekusi.hpp"

std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nusantara::WaktuEksekusi::waktuMulai; // NOLINT

std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nusantara::WaktuEksekusi::waktuSelesai; // NOLINT

void nusantara::WaktuEksekusi::mulai()
{
  nusantara::WaktuEksekusi::waktuMulai = std::chrono::high_resolution_clock::now();
} // function nusantara::WaktuEksekusi::mulai

void nusantara::WaktuEksekusi::selesai()
{
  nusantara::WaktuEksekusi::waktuSelesai = std::chrono::high_resolution_clock::now();
} // function nusantara::WaktuEksekusi::selesai

void nusantara::WaktuEksekusi::cetak()
{
  auto waktuSelesai = std::chrono::high_resolution_clock::now();

  auto durasiWaktuEksekusi = std::chrono::duration_cast<std::chrono::microseconds>(waktuSelesai - nusantara::WaktuEksekusi::waktuMulai).count();

  auto durasiDalamJam = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL * 60LL);

  durasiWaktuEksekusi %= (1000LL * 1000LL * 60LL * 60LL);

  auto durasiDalamMenit = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL);

  auto durasiDalamDetik = durasiWaktuEksekusi / (1000LL * 1000LL);

  auto durasiDalamMiliDetik = durasiWaktuEksekusi / 1000LL;

  auto durasiDalamMicroDetik = durasiWaktuEksekusi % 1000LL;

  nusantara::cetakDF("\nDurasi waktu eksekusi: {} jam, {} menit, {} detik, {} milidetik, {} microdetik", durasiDalamJam, durasiDalamMenit, durasiDalamDetik, durasiDalamMiliDetik,
      durasiDalamMicroDetik); // function nusantara::cetakDF

} // function nusantara::WaktuEksekusi::cetak