/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */


#include <functional>
#include <algorithm>
#include <utility>
#include <cstddef>
#include <format>
#include <string>
#include <vector>
#include <regex>

#include "perintah/perintah.hpp"
#include "cetak/cetak.hpp"


nusantara::Perintah::Perintah(
  std::string nama,
  std::string deskripsi,
  std::function<void(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &kumpulanArgumen)> intruksi,
  const bool &tanpaArgumen
): Perintah(
  std::regex(nama),
  std::move(nama),
  std::move(deskripsi),
  std::move(intruksi),
  tanpaArgumen
) {}

nusantara::Perintah::Perintah(
  std::regex regex,
  std::string nama,
  std::string deskripsi,
  std::function<void(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &kumpulanArgumen)> intruksi,
  const bool &tanpaArgumen
):
regex(std::move(regex)),
nama(std::move(nama)),
deskripsi(std::move(deskripsi)),
intruksi(std::move(intruksi)),
tanpaArgumen(tanpaArgumen)
{}

const std::string& nusantara::Perintah::ambilNama() const {
  return this->nama;
}

const std::string& nusantara::Perintah::ambilDeskripsi() const {
  return this->deskripsi;
}

const std::regex& nusantara::Perintah::ambilRegex() const {
  return this->regex;
}

std::string nusantara::Perintah::ubahKeString() const  {
  return std::format(
    "{} - {}",
    this->nama,
    this->deskripsi
  );
}

void nusantara::Perintah::eksekusi(EksekusiPerintah &eksekusiPerintah, size_t &indeksSaatIni, std::vector<std::string> &argumen) {
  if(this->tanpaArgumen && argumen.size() > 2) {
    nstd::cetakDF("Perintah {} tidak memerlukan argumen.", this->nama);
    return;
  }
  this->intruksi(eksekusiPerintah, indeksSaatIni, argumen);
}

bool nusantara::Perintah::operator==(const Perintah& lain) {
  return this->nama == lain.nama || this->deskripsi == lain.deskripsi;
}

void nusantara::EksekusiPerintah::tambah(Perintah perintah) {
  if(std::find(this->kumpulanPerintah.begin(), this->kumpulanPerintah.end(), perintah) == this->kumpulanPerintah.end()) {
    this->kumpulanPerintah.push_back(std::move(perintah));
  }
}

const std::vector<nusantara::Perintah>& nusantara::EksekusiPerintah::ambilKumpulanPerintah() {
  return this->kumpulanPerintah;
}

void nusantara::EksekusiPerintah::eksekusi(std::vector<std::string> argumen) {
  size_t currentIndex = 1;

  if(argumen.size() == 1) {
    this->kumpulanPerintah[0].eksekusi(*this, currentIndex, argumen);
    return;
  }
  
  for(auto& perintah: this->kumpulanPerintah) {
    if(std::regex_match(argumen[currentIndex], perintah.ambilRegex())) {
      perintah.eksekusi(*this, currentIndex, argumen);
      currentIndex++;
      return;
    }
  }

  nstd::cetakDF("Perintah '{}' tidak ada.", argumen[currentIndex]);
}