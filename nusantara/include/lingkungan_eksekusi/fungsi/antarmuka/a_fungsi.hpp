/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef A_FUNGSI_HPP
#define A_FUNGSI_HPP

#include <string>

namespace nusantara {

class AFungsi
{
  public:
  virtual ~AFungsi() = default;
  virtual void panggil() = 0;
  virtual const std::string& ambilNama() = 0;
  // akhir dari access modifiers public

}; // class AFungsi

} // namespace nusantara

#endif
