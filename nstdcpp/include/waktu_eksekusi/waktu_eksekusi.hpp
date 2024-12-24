/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

// Blokir pengulangan header
#pragma once


#include <chrono>


namespace nstd {

  /**
  * @class WaktuEksekusi
  *
  * @brief Kelas ini digunakan untuk mengukur waktu eksekusi program.
  *
  * @details Kelas ini menggunakan timersteady_clock untuk menghitung waktu yang berlaku selama eksekusi program. Dengan demikian, kita dapat memperoleh informasi tentang waktu yang dibutuhkan untuk melaksanakan suatu proses.
  */
  class WaktuEksekusi {
    public:
      /**
      * @brief Menginisiasi timer untuk mengukur waktu eksekusi.
      *
      * @details Pada saat ini, kita tidak melakukan apa-apa karena kita belum memulai eksekusi program. Namun, pada saat lain, kita akan menyimpan waktu ini sebagai nilai awal waktu mulai.
      */
      static void mulai();
      
      /**
      * @brief Memperbarui nilai waktu selesai.
      *
      * @details Pada saat ini, kita tidak melakukan apa-apa karena kita belum selesai eksekusi program. Namun, pada saat lain, kita akan memperbarui nilai waktu ini sebagai nilai akhir waktu selesai setelah suatu proses selesai dilaksanakan.
      */
      static void selesai();
      
      /**
      * @brief Menampilkan informasi tentang waktu eksekusi.
      *
      * @details Pada saat ini, kita tidak melakukan apa-apa karena kita belum menampilkan informasi tentang waktu eksekusi. Namun, pada saat lain, kita akan menampilkan nilai-nilai yang telah dihitung sebagai waktu mulai dan waktu selesai untuk memberikan informasi tentang waktu yang dibutuhkan untuk melaksanakan suatu proses.
      */
      static void cetak();
  
    private:
      /**
      * @brief Nilai waktu mulai saat eksekusi program dimulai.
      *
      * @details Sebagai contoh, kita dapat menggunakan nilai ini sebagai batas waktu awal untuk suatu proses. Setelah proses selesai dilaksanakan, kita dapat membandingkan nilai ini dengan nilai waktu akhir untuk mengetahui seberapa lama waktu yang dibutuhkan.
      */
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuMulai; // NOLINT
      
      /**
      * @brief Nilai waktu selesai saat eksekusi program selesai.
      *
      * @details Sebagai contoh, kita dapat menggunakan nilai ini sebagai batas waktu akhir untuk suatu proses. Setelah proses selesai dilaksanakan, kita dapat membandingkan nilai ini dengan nilai waktu mulai untuk mengetahui seberapa lama waktu yang dibutuhkan.
      */
      static std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<long long, std::ratio<1LL, 1000000000LL>>> waktuSelesai; // NOLINT
  };

}// nstd