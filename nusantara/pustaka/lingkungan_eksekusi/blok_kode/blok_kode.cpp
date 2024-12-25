/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "lingkungan_eksekusi/intruksi/kumpulan_intruksi.hpp"
#include "lingkungan_eksekusi/fungsi/kumpulan_fungsi.hpp"
#include "lingkungan_eksekusi/blok_kode/blok_kode.hpp"

nusantara::BlokKode::BlokKode(
  KumpulanFungsi &&kumpulanFungsi,
  KumpulanIntruksi &&kumpulanIntruksi
): 
kumpulanIntruksi(std::move(kumpulanIntruksi)), 
kumpulanFungsi(std::move(kumpulanFungsi)) 
{} // constructor BlokKode

nusantara::KumpulanIntruksi& nusantara::BlokKode::ambilKumpulanIntruksi() {
  return this->kumpulanIntruksi;
} // function ambilKumpulanIntruksi

nusantara::KumpulanFungsi& nusantara::BlokKode::ambilKumpulanFungsi() {
  return this->kumpulanFungsi;
} // function ambilKumpulanFungsi