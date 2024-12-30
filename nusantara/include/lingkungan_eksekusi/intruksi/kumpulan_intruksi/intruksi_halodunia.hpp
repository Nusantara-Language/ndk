/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef INTRUKSI_HALODUNIA_HPP
#define INTRUKSI_HALODUNIA_HPP

#include "lingkungan_eksekusi/intruksi/intruksi.hpp"

namespace nusantara {

class IntruksiHaloDunia : public Intruksi
{
  public:
  IntruksiHaloDunia() = default;

  void jalankan() override;
  // akhir dari access modifiers public

}; // class IntruksiHaloDunia

} // namespace nusantara

#endif
