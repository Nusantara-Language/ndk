/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "pengecualian/antarmuka/a_pengecualian.h"
#include <string>

const char* nusantara::APengecualian::what() const noexcept {
  return this->pesan.c_str();
}

const std::string& nusantara::APengecualian::ambilPesan() {
  return this->pesan;
}