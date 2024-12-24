#include "token/kumpulan_token_regex/token_regex_nusantara.hpp"

auto nusantara::nusantaraTokenRegexs() -> const std::set<TokenRegex>& 
{
  const static std::set<TokenRegex> result = {
    TokenRegex{std::regex("^[(]"), TokenType::kurungBulatBuka},
    TokenRegex{std::regex("^[)]"), TokenType::kurungBulatTutup},
    TokenRegex{std::regex("^[\n]"), TokenType::barisBaru},
    TokenRegex{std::regex("^\\s"), TokenType::ruangKosong},
    TokenRegex{std::regex("^;"), TokenType::titikKoma},
    TokenRegex{std::regex("^[a-zA-Z][a-zA-Z0-9_]*"), TokenType::identifikasi},
    TokenRegex{std::regex("^."), TokenType::tidakDiketahui},
  };
  return result;
}