/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef TOKEN_REGEX_HPP
#define TOKEN_REGEX_HPP

#include <regex>
#include <utility>

#include "token/tipe_token.hpp"

namespace nusantara {

class TokenRegex
{
  public:
  TokenRegex(std::regex regex, const TipeToken& tipe) : regex(std::move(regex)), tipe(tipe) {}

  [[nodiscard]] const std::regex& ambilRegex() const
  {
    return regex;
  }

  [[nodiscard]] const TipeToken& ambilTipe() const
  {
    return tipe;
  }

  bool operator<(const TokenRegex& lain) const
  {
    return tipe < lain.tipe;
  }

  bool operator>(const TokenRegex& lain) const
  {
    return tipe > lain.tipe;
  }

  // akhir dari access modifiers public

  private:
  std::regex regex;

  TipeToken tipe;
  // akhir dari access modifiers private

}; // class TokenRegex

} // namespace nusantara

#endif
