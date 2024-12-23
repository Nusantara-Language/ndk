#pragma once

// Include STD C++
#include <string>

// Namespace
namespace nusantara 
{
  enum TokenType 
  {
    kurungBulatBuka,
    kurungBulatTutup,
    barisBaru,
    ruangKosong,
    titikKoma,
    identifikasi,
    tidakDiketahui,
    akhirDariFile,
  };

  auto tokenTypeToString(const TokenType& type) -> std::string;
}  // namespace nusantara