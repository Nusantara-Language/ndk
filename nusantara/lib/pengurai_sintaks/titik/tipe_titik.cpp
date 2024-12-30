/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "pengurai_sintaks/titik/tipe_titik.hpp"
#include "catatan/catatan.ap.hpp"
#include "konfig/konfig_label_keluaran.hpp"

std::string nusantara::tipeTitikKeString(const TipeTitik& type)
{
  switch (type)
  {
  case TOKEN:
    return "TOKEN";
  case AWAL:
    return "AWAL";
  case PERNYATAAN:
    return "PERNYATAAN";
  case EKSPRESI:
    return "EKSPRESI";
  case PANGGIL_FUNGSI:
    return "PANGGIL FUNGSI";
  default:
    __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Fungsi tipeTitikKeString"),
        "Tipe titik tidak dapat di ubah menjadi string."); // __CATATAN__KESALAHAN_FATAL_M__
    break;
  } // switch

} // function tipeTitikKeString