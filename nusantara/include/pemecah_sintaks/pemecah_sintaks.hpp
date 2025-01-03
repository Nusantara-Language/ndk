/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PEMECAH_SINTAKS_HPP
#define PEMECAH_SINTAKS_HPP

#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "token/tipe_token.hpp"
#include "token/token.hpp"
#include "token/token_regex.hpp"
#include <regex>
#include <set>
#include <string>

namespace nusantara {

class PemecahSintaks
{
  public:
  explicit PemecahSintaks(std::set<TokenRegex> tokenRegexs) : tokenRegexs(std::move(tokenRegexs)), lokasiToken({1, 1}), pengecualianSintaks() {}

  void aturLokasiBerkas(const std::string& lokasiBerkas);

  void aturKonten(const std::string& konten);

  void tokenisasi();

  [[nodiscard]] const std::vector<Token>& ambilHasil() const;

  auto cetak() -> void;
  // akhir dari access modifiers public

  private:
  std::string lokasiBerkas;
  std::string konten;

  PengecualianSintaks pengecualianSintaks;

  std::set<TokenRegex> tokenRegexs;

  std::vector<Token> hasilTokenisasi;

  LokasiToken lokasiToken;

  void buatToken(Token& token);

  void buatBanyakToken();

  void membuatToken(const std::smatch& dataYangSama, const TipeToken& tipeToken, Token& token);
  // akhir dari access modifiers private

}; // class PemecahSintaks

} // namespace nusantara

#endif
