/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <memory>

#include "lingkungan_eksekusi/intruksi/kumpulan_intruksi/intruksi_halodunia.hpp"
#include "lingkungan_eksekusi/fungsi/kumpulan_fungsi/fungsi_halodunia.hpp"
#include "lingkungan_eksekusi/fungsi/fungsi.hpp"

nusantara::FungsiHaloDunia::FungsiHaloDunia(): Fungsi("halodunia")  {
  this->blokKode.ambilKumpulanIntruksi().tambahIntruksi(std::move(std::make_unique<IntruksiHaloDunia>()));
} // constructor FungsiHaloDunia

