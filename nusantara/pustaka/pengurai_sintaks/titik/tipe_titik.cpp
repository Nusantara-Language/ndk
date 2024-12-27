/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <iostream>

#include "pengurai_sintaks/titik/tipe_titik.hpp"
#include "konfig/konfig_label_keluaran.hpp"
#include "catatan/catatan.ap.hpp"

std::string nusantara::tipeTitikKeString(const TipeTitik &type) {
  switch(type) {
    case AWAL:
      return "AWAL";
    case PERNYATAAN:
      return "PERNYATAAN";
    case PANGGIL_FUNGSI:
      return "PANGGIL FUNGSI";
    case TEMPAT_PARAMETER_PANGGIL_FUNGSI:
      return "TEMPAT PARAMETER PANGGIL FUNGSI";
    case TOKEN:
      return "TOKEN";
    case AKHIR_DARI_FILE:
      return "AKHIR_DARI_FILE";
    case BILANGAN:
      return "BILANGAN";
    default:
      __CATATAN__KESALAHAN_FATAL_M__(
        __NK__LABEL_KELUARAN_CUSTOM__("Fungsi tipeTitikKeString"),
        "Tipe titik tidak dapat di ubah menjadi string."
      ); // __CATATAN__KESALAHAN_FATAL_M__
      break;
  } // switch
  
} // function tipeTitikKeString