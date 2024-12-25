/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include "penganalisis_semantik/penganalisis_semantik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"

bool nusantara::PenganalisisSemantik::kunjungiTitikToken(const Titik&) {
  return true;
} // function kunjungiTitikToken

bool nusantara::PenganalisisSemantik::kunjungiTitikPanggilFungsi(const Titik& titik) {
  if(titik.ambilKumpulanTitikTurunan().empty()) {
    std::cerr << "[AS] Kesalahan: pemanggilan fungsi tanpa nama" << std::endl;
    return false;
  } // if

  const std::string functionName = titik.ambilKumpulanTitikTurunan()[0]->ambilToken()->konten;
  if (functionName != "halodunia") {
    std::cerr << "[AS] Kesalahan: fungsi '" << functionName << "' tidak dikenali." << std::endl;
    return false;
  } // if

  return true;
} // function kunjungiTitikPanggilFungsi

bool nusantara::PenganalisisSemantik::kunjungiTitikAwal(const Titik& titik) {
  return std::all_of(titik.ambilKumpulanTitikTurunan().begin(), titik.ambilKumpulanTitikTurunan().end(), [this](const std::unique_ptr<Titik>& titikTurunan) { return titikTurunan->terima<bool>(*this); });
} // function kunjungiTitikAwal 

bool nusantara::PenganalisisSemantik::kunjungiTitikPernyataanEkspresi(const Titik& titik) {
  return std::all_of(titik.ambilKumpulanTitikTurunan().begin(), titik.ambilKumpulanTitikTurunan().end(), [this](const std::unique_ptr<Titik>& titikTurunan) { return titikTurunan->terima<bool>(*this); });
} // function kunjungiTitikPernyataanEkspresi

bool nusantara::PenganalisisSemantik::kunjungiTitikTempatParameterPanggilFungsi(const Titik&) {
  return true;
} // function kunjungiTitikTempatParameterPanggilFungsi
