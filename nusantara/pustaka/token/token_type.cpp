#include "token/token_type.hpp"
#include <iostream>

auto nusantara::tokenTypeToString(TokenType const& type) -> std::string 
{
  switch (type) {
    case TokenType::tidakDiketahui: return "tidak diketahui";
    case TokenType::ruangKosong: return "ruang kosong";
    case TokenType::barisBaru: return "baris baru";
    case TokenType::akhirDariFile: return "akhir dari file";
    case TokenType::identifikasi: return "identifikasi";
    case TokenType::kurungBulatBuka: return "kurung bulat buka";
    case TokenType::kurungBulatTutup: return "kurung bulat tutup";
    case TokenType::titikKoma: return "titik koma";
    default: std::cerr << "Tipe token tidak dapat diubah ke string." << "\n"; break;
  }
}