#include "runtime/fungsi/fungsi.hpp"
#include "runtime/kawasan/kawasan.hpp"

nusantara::Fungsi::Fungsi(
  const std::string& nama
): nama(nama), kawasan({}, {}) {}

nusantara::Fungsi::Fungsi(
  const std::string& nama, 
  Kawasan&& kawasan
): nama(nama), kawasan(std::move(kawasan)) {}

void nusantara::Fungsi::panggil() {
  this->kawasan.ambilKumpulanIntruksi().jalankan();
}

const std::string& nusantara::Fungsi::ambilNama() {
  return this->nama;
}