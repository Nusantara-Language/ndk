/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "lingkungan_eksekusi/intruksi/kumpulan_intruksi.hpp"

nusantara::KumpulanIntruksi::KumpulanIntruksi() : isinya() {}

nusantara::KumpulanIntruksi::KumpulanIntruksi(std::vector<std::unique_ptr<Intruksi>>&& isinya) : isinya(std::move(isinya)) {}

void nusantara::KumpulanIntruksi::jalankan()
{
  for (const auto& intruksi : this->isinya)
  {
    if (intruksi != nullptr)
    {
      intruksi->jalankan();
    }
  }
} // function jalankan

void nusantara::KumpulanIntruksi::tambahIntruksi(std::unique_ptr<Intruksi>&& intruksi)
{
  this->isinya.push_back(std::move(intruksi));
} // function tambahIntruksi
