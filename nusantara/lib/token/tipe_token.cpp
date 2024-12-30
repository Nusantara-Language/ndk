/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "token/tipe_token.hpp"
#include "catatan/catatan.ap.hpp"
#include "konfig/konfig_label_keluaran.hpp"

std::string nusantara::tipeTokenKeString(TipeToken const& type)
{
  switch (type)
  {
  case TipeToken::tidakDiketahui:
    return "tidak diketahui";
  case TipeToken::ruangKosong:
    return "ruang kosong";
  case TipeToken::barisBaru:
    return "baris baru";
  case TipeToken::akhirDariFile:
    return "akhir dari file";
  case TipeToken::muat:
    return "muat";
  case TipeToken::nilaiBilangan:
    return "nilai bilangan";
  case TipeToken::nilaiTeks:
    return "nilai teks";
  case TipeToken::identifikasi:
    return "identifikasi";
  case TipeToken::kurungBulatBuka:
    return "kurung bulat buka";
  case TipeToken::kurungBulatTutup:
    return "kurung bulat tutup";
  case TipeToken::titikKoma:
    return "titik koma";
  default:
    __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Fungsi tipeTokenKeString"),
        "Tipe token tidak dapat diubah ke string."); // __CATATAN__KESALAHAN_FATAL_M__
    break;
  } // switch
} // function tipeTokenKeString