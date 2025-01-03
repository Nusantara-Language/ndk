/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <exception>

#include "abp/abp.hpp"
#include "catatan/catatan.ap.hpp"

int main(int argc, const char* argv[])
{
  try
  {
    return nusantara::abp(argc, *argv);
  }
  catch (const std::exception& kesalahan)
  {
    __CATATAN__KESALAHAN_FATAL__(kesalahan.what());
  }
}