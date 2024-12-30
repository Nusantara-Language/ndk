/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PENGECUALIAN_PENGURAI_SINTAKS_HPP
#define PENGECUALIAN_PENGURAI_SINTAKS_HPP

#include <string>

#include "pengecualian/antarmuka/a_pengecualian.h"

namespace nusantara {

struct PengecualianPenguraiSintaks : public APengecualian
{
  explicit PengecualianPenguraiSintaks(const std::string& pesan) : APengecualian(pesan) {}
}; // struct PengecualianPenguraiSintaks

} // namespace nusantara

#endif
