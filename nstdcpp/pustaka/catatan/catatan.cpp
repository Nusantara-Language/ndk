/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "catatan/catatan.hpp"

#ifdef CATATAN

#ifdef CATATAN_SIMPAN_BERKAS
  #include <filesystem>
  #include <fstream>
  
  #include "alat.hpp"
#endif

#if defined(CATATAN_PERLIHATKAN_INFO) || defined(CATATAN_PERLIHATKAN_KESALAHAN) || defined(CATATAN_PERLIHATKAN_PERINGATAN)
  #include <iostream>
#endif

#ifdef CATATAN_SIMPAN_BERKAS

  nstd::Catatan* nstd::Catatan::instance = nullptr;

  nstd::Catatan::Catatan() {
      // Mengatur nama folder catatan
      Catatan::lokasiFolder = nstd::ambilLokasiBerkasProgram().parent_path().string() + "/.catatan";

      // Buat folder catatan jika belum ada
      if (!std::filesystem::exists(Catatan::lokasiFolder)) {
        std::filesystem::create_directory(Catatan::lokasiFolder);
      } // if

      // Mengatur nama berkas catatan
      auto now = std::chrono::system_clock::now();
      auto now_time = std::chrono::system_clock::to_time_t(now);
      auto now_tm = *std::localtime(&now_time);
      Catatan::namaBerkas = std::to_string(now_tm.tm_mday) + "-";
      Catatan::namaBerkas += std::to_string(now_tm.tm_mon + 1) + "-";
      Catatan::namaBerkas += std::to_string(now_tm.tm_year + 1900) + "-";
      Catatan::namaBerkas += std::to_string(now_tm.tm_hour) + "-";
      Catatan::namaBerkas += std::to_string(now_tm.tm_min) + "-";
      Catatan::namaBerkas += std::to_string(now_tm.tm_sec) + ".catatan";

      // Mengatur lokasi berkas catatan
      Catatan::lokasiBerkas = Catatan::lokasiFolder + "/" + Catatan::namaBerkas;

      // Buat berkas catatan jika belum ada
      if (!std::filesystem::exists(Catatan::lokasiBerkas)) {
        std::ofstream file(Catatan::lokasiBerkas);
        file.close();
      } // if
  } // constructor Catatan

  nstd::Catatan::~Catatan() {
    delete Catatan::instance;
  } // destructor Catatan

  nstd::Catatan* nstd::Catatan::ambilInstance() {
    if(Catatan::instance == nullptr) {
      // Jika instance belum ada, buat instance baru
      Catatan::instance = new Catatan();
    }// if
    return Catatan::instance;
  } // function ambilInstance
#endif

void nstd::Catatan::info(const std::string& pesan) {
  #ifdef CATATAN_PERLIHATKAN_INFO
    std::cout << "\033[1;33m[CATATAN][INFO]\033[0m " << pesan << std::endl;
    #ifdef CATATAN_SIMPAN_BERKAS
      std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
      file << "[CATATAN][INFO] " << pesan << std::endl;
      file.close();
    #endif
  #endif
}

void nstd::Catatan::kesalahan(const std::string& pesan) {
  #ifdef CATATAN_PERLIHATKAN_KESALAHAN
    std::cout << "\033[1;31m[CATATAN][KESALAHAN]\033[0m " << pesan << std::endl;
    #ifdef CATATAN_SIMPAN_BERKAS
      std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
      file << "[CATATAN][KESALAHAN] " << pesan << std::endl;
      file.close();
    #endif
  #endif
}

void nstd::Catatan::peringatan(const std::string& pesan) {
  #ifdef CATATAN_PERLIHATKAN_PERINGATAN
    std::cout << "\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m " << pesan << std::endl;
    #ifdef CATATAN_SIMPAN_BERKAS
      std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
      file << "[CATATAN][PERINGATAN] " << pesan << std::endl;
      file.close();
    #endif
  #endif
}

#endif
