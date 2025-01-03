/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef KUMPULAN_FUNGSI_HPP
#define KUMPULAN_FUNGSI_HPP

#include "lingkungan_eksekusi/fungsi/antarmuka/a_fungsi.hpp"
#include <memory>
#include <string>
#include <vector>

namespace nusantara {

class KumpulanFungsi
{
  public:
  KumpulanFungsi();

  KumpulanFungsi(std::vector<std::unique_ptr<AFungsi>>&& isinya);

  void panggilFungsi(const std::string& nama);

  void tambahFungsi(std::unique_ptr<AFungsi>&& intruksi);
  // akhir dari access modifiers public

  private:
  std::vector<std::unique_ptr<AFungsi>> isinya;
  // akhir dari access modifiers private

}; // class KumpulanFungsi

} // namespace nusantara

#endif
