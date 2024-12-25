/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <iostream>

#include "token/tipe_token.hpp"

std::string nusantara::tipeTokenKeString(TipeToken const& type)
{
  switch (type) {
    case TipeToken::tidakDiketahui: return "tidak diketahui";
    case TipeToken::ruangKosong: return "ruang kosong";
    case TipeToken::barisBaru: return "baris baru";
    case TipeToken::akhirDariFile: return "akhir dari file";
    case TipeToken::identifikasi: return "identifikasi";
    case TipeToken::kurungBulatBuka: return "kurung bulat buka";
    case TipeToken::kurungBulatTutup: return "kurung bulat tutup";
    case TipeToken::titikKoma: return "titik koma";
    default: std::cerr << "Tipe token tidak dapat diubah ke string." << "\n"; break;
  } // switch
} // function tipeTokenKeString