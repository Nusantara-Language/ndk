/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PENGURAI_SINTAKS_HPP
#define PENGURAI_SINTAKS_HPP

#include <memory>
#include <string>
#include <vector>

#include "pendengar/a_pendengar_titik.hpp"
#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "titik/titik.hpp"
#include "token/token.hpp"

namespace nusantara {

class PenguraiSintaks
{
  public:
  explicit PenguraiSintaks(const bool& psa, const std::shared_ptr<std::vector<std::string>>& lokasiBerkasYangSudahDiMuat) : psa(psa), pengecualianSintaks(), kumpulanlokasiBerkasYgSudahDiMuat(lokasiBerkasYangSudahDiMuat) {}

  explicit PenguraiSintaks(const bool& psa) : psa(psa), pengecualianSintaks(), kumpulanlokasiBerkasYgSudahDiMuat(std::make_shared<std::vector<std::string>>()) {}

  explicit PenguraiSintaks() : PenguraiSintaks(false) {}

  void aturKumpulanToken(const std::vector<nusantara::Token>& kumpulanToken);

  [[nodiscard]] const std::unique_ptr<Titik>& ambilHasil() const;

  void uraikan();

  void cetak();
  // akhir dari access modifiers public

  private:
  size_t indeksTokenSaatIni = 0;

  std::vector<nusantara::Token> kumpulanToken;

  std::unique_ptr<Titik> hasilPenguraian;

  PengecualianSintaks pengecualianSintaks;

  std::shared_ptr<std::vector<std::string>> kumpulanlokasiBerkasYgSudahDiMuat;

  bool psa;

  [[nodiscard]] const nusantara::Token& tokenSaatIni() const;

  [[nodiscard]] bool apakahSudahDiAkhirFile() const;

  [[nodiscard]] bool cekTipeToken(const nusantara::TipeToken& tipe) const;

  [[nodiscard]] bool cekTipeToken(const std::vector<nusantara::TipeToken>& kumpulanTipeToken) const;

  const Token& tokenSebelumnya();

  const nusantara::Token& majuKeTokenSelanjutnya();

  const nusantara::Token& makanToken(const TipeToken& tipe, const std::string& pesanKesalahan);

  bool apakahTokenSaatIniAdalah(const std::vector<nusantara::TipeToken>& kumpulanTipeToken);

  std::unique_ptr<Titik> uraiPernyataan();

  std::unique_ptr<Titik> uraiEkspresi();

  std::unique_ptr<Titik> uraiMuatBerkas();

  std::unique_ptr<Titik> uraiPanggilFungsi();
  // akhir dari access modifiers private

}; // class PenguraiSintaks

} // namespace nusantara

#endif
