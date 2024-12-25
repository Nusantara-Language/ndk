/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <filesystem>
#include <fstream>

#include "catatan/catatan.hpp"
#include "alat.hpp"

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
