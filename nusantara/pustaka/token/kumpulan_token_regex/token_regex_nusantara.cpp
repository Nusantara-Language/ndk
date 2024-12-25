/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "token/kumpulan_token_regex/token_regex_nusantara.hpp"

const std::set<nusantara::TokenRegex>& nusantara::nusantaraTokenRegexs()
{
  const static std::set<TokenRegex> result = {
    TokenRegex{std::regex("^[(]"), TipeToken::kurungBulatBuka},
    TokenRegex{std::regex("^[)]"), TipeToken::kurungBulatTutup},
    TokenRegex{std::regex("^[\n]"), TipeToken::barisBaru},
    TokenRegex{std::regex("^\\s"), TipeToken::ruangKosong},
    TokenRegex{std::regex("^;"), TipeToken::titikKoma},
    TokenRegex{std::regex("^[a-zA-Z][a-zA-Z0-9_]*"), TipeToken::identifikasi},
    TokenRegex{std::regex("^."), TipeToken::tidakDiketahui}
  }; // variable result
  return result;
} // function nusantaraTokenRegexs