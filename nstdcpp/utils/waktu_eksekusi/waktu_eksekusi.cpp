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


/**
 * @brief Variable untuk menampung waktu mulai eksekusi program.
 * @note waktuMulai digunakan untuk merekam waktu sebelum program dijalankan.
 */
std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuMulai;  // NOLINT

/**
 * @brief Variable untuk menampung waktu selesai eksekusi program.
 *
 * @note waktuSelesai digunakan untuk merekam waktu setelah program dijalankan.
 */
std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> nstd::WaktuEksekusi::waktuSelesai;  // NOLINT

/**
 * @brief Metodo untuk menyiapkan waktu mulai eksekusi program.
 *
 * @details Kode ini digunakan untuk merekam waktu sebelum program dijalankan.
 *         Fungsi ini diperlukan untuk menghitung durasi waktu eksekusi program.
 *
 * @note Waktu mulai diisyaratkan untuk merekam waktu sebelum program dijalankan.
 */
void nstd::WaktuEksekusi::mulai() {
  /**
   * @brief Menyiapkan waktu mulai eksekusi program.
   *
   * @details Saat ini, waktu mulai disimpan menggunakan clock resolusi tinggi.
   */
  nstd::WaktuEksekusi::waktuMulai = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Metodo untuk menyelesaikan waktu eksekusi program.
 *
 * @details Kode ini digunakan untuk merekam waktu setelah program dijalankan.
 *         Fungsi ini diperlukan untuk menghitung durasi waktu eksekusi program.
 *
 * @note Waktu selesai diisyaratkan untuk merekam waktu setelah program dijalankan.
 *
 * @note This method is called after the program execution to record the end time.
 *
 * @param none
 */
void nstd::WaktuEksekusi::selesai() {
 /**
  * @brief Merekam waktu selesai eksekusi program.
  *
  * @details Saat ini, waktu selesai disimpan menggunakan clock resolusi tinggi.
  *
  * @note It is important to record the end time using a high-resolution clock to ensure accurate timing.
  */
 nstd::WaktuEksekusi::waktuSelesai = std::chrono::high_resolution_clock::now();
}

/**
 * @brief Metodo untuk mencetak durasi waktu eksekusi program.
 *
 * @details Kode ini digunakan untuk mencetak durasi waktu eksekusi program yang telah dijalankan.
 *         Fungsi ini diperlukan untuk memberikan informasi tentang berapa lama program telah dijalankan.
 *
 * @note Durasi waktu eksekusi adalah waktu yang dibutuhkan program untuk diselesaikan.
 *
 * @param none
 *
 * @return none
 */
void nstd::WaktuEksekusi::cetak() {
  /**
   * @brief Merekam waktu selesai eksekusi program.
   *
   * @details Saat ini, waktu selesai disimpan menggunakan clock resolusi tinggi.
   */
  auto waktuSelesai = std::chrono::high_resolution_clock::now();

  /**
   * @brief Menghitung durasi waktu eksekusi program.
   *
   * @details Durasi waktu eksekusi dihitung dengan cara mengurangi waktu mulai eksekusi dengan waktu selesai eksekusi.
   *         Nilai hasilnya digunakan untuk menghitung durasi waktu eksekusi dalam berbagai satuan waktu.
   */
  auto durasiWaktuEksekusi = std::chrono::duration_cast<std::chrono::microseconds>(waktuSelesai - nstd::WaktuEksekusi::waktuMulai).count();

  /**
   * @brief Menghitung durasi waktu eksekusi dalam jam.
   *
   * @details Durasi waktu eksekusi dalam jam dihitung dengan cara membagi durasi waktu eksekusi dengan 1000*1000*60*60.
   *         Nilai hasilnya digunakan untuk mencetak durasi waktu eksekusi dalam satuan jam.
   */
  auto durasiDalamJam = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL * 60LL); // NOLINT

  /**
   * @brief Menghitung durasi waktu eksekusi dalam satuan lain.
   *
   * @details Proses penghitungan durasi waktu eksekusi dalam satuan lain (menit, detik, milidetik, microdetik)
   *         dilakukan dengan cara mengurangi durasi waktu eksekusi dengan nilai hasil dari penghitungan sebelumnya.
   */
  durasiWaktuEksekusi %= (1000LL * 1000LL * 60LL * 60LL); // NOLINT

  /**
   * @brief Menghitung durasi waktu eksekusi dalam menit.
   *
   * @details Durasi waktu eksekusi dalam menit dihitung dengan cara membagi durasi waktu eksekusi dengan 1000*1000*60.
   *         Nilai hasilnya digunakan untuk mencetak durasi waktu eksekusi dalam satuan menit.
   */
  auto durasiDalamMenit = durasiWaktuEksekusi / (1000LL * 1000LL * 60LL); // NOLINT

  /**
   * @brief Menghitung durasi waktu eksekusi dalam detik.
   *
   * @details Durasi waktu eksekusi dalam detik dihitung dengan cara membagi durasi waktu eksekusi dengan 1000*1000.
   *         Nilai hasilnya digunakan untuk mencetak durasi waktu eksekusi dalam satuan detik.
   */
  auto durasiDalamDetik = durasiWaktuEksekusi / (1000LL * 1000LL); // NOLINT

  /**
   * @brief Menghitung durasi waktu eksekusi dalam milidetik.
   *
   * @details Durasi waktu eksekusi dalam milidetik dihitung dengan cara membagi durasi waktu eksekusi dengan 1000.
   *         Nilai hasilnya digunakan untuk mencetak durasi waktu eksekusi dalam satuan milidetik.
   */
  auto durasiDalamMiliDetik = durasiWaktuEksekusi / 1000LL; // NOLINT

  /**
   * @brief Menghitung durasi waktu eksekusi dalam microdetik.
   *
   * @details Durasi waktu eksekusi dalam microdetik dihitung dengan cara mengambil sisa dari penghitungan sebelumnya.
   *         Nilai hasilnya digunakan untuk mencetak durasi waktu eksekusi dalam satuan microdetik.
   */
  auto durasiDalamMicroDetik = durasiWaktuEksekusi % 1000LL; // NOLINT
  
  /**
   * @brief Mencetak durasi waktu eksekusi.
   *
   * @details Durasi waktu eksekusi dicetak dalam berbagai satuan waktu menggunakan fungsi cetakDF.
   *         Parameter cetakDF adalah format cetak, durasi waktu eksekusi dalam jam, menit, detik, milidetik, dan microdetik.
   */
  nstd::cetakDF(
    "\nDurasi waktu eksekusi: {} jam, {} menit, {} detik, {} milidetik, {} microdetik", 
    durasiDalamJam, 
    durasiDalamMenit, 
    durasiDalamDetik, 
    durasiDalamMiliDetik, 
    durasiDalamMicroDetik
  );
}