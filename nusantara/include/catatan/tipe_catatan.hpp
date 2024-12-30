/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef TIPE_CATATAN_HPP
#define TIPE_CATATAN_HPP

#include "konfig/konfig_catatan.hpp"

#ifdef __NK__CATATAN_AKTIF__

namespace nusantara {

enum TipeCatatan
{
  DEBUG,
  INFO,
  PERINGATAN,
  KESALAHAN,
  KESALAHAN_FATAL,
}; // enum TipeCatatan

} // namespace nusantara

#endif

#endif
