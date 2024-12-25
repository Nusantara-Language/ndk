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
#include "lingkungan_eksekusi/kawasan/kawasan.hpp"

nusantara::Kawasan::Kawasan(
  KumpulanFungsi &&kumpulanFungsi,
  KumpulanIntruksi &&kumpulanIntruksi
): 
kumpulanIntruksi(std::move(kumpulanIntruksi)), 
kumpulanFungsi(std::move(kumpulanFungsi)) 
{} // constructor Kawasan

nusantara::KumpulanIntruksi& nusantara::Kawasan::ambilKumpulanIntruksi() {
  return this->kumpulanIntruksi;
} // function ambilKumpulanIntruksi

nusantara::KumpulanFungsi& nusantara::Kawasan::ambilKumpulanFungsi() {
  return this->kumpulanFungsi;
} // function ambilKumpulanFungsi