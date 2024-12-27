/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pendengar/a_pendengar_titik.hpp"
#include "token/token.hpp"
#include "titik/titik.hpp"

namespace nusantara {

  class PenguraiSintaks {
    public:
      explicit PenguraiSintaks(const bool &psa): psa(psa), pengecualianSintaks() {}

      explicit PenguraiSintaks(): PenguraiSintaks(false) {}

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

      bool psa;

      [[nodiscard]] const nusantara::Token & tokenSaatIni() const;

      [[nodiscard]] bool apakahSudahDiAkhirFile() const;

      [[nodiscard]] bool cekTipeToken(const nusantara::TipeToken &tipe) const;

      const Token & tokenSebelumnya();

      const nusantara::Token & majuKeTokenSelanjutnya();

      const nusantara::Token & makanToken(const TipeToken &tipe, const std::string &pesanKesalahan);

      bool apakahTokenSaatIniAdalah(const std::vector<nusantara::TipeToken> &kumpulanTipeToken);

      std::unique_ptr<Titik> uraiPernyataanEkspresi();

      std::unique_ptr<Titik> uraiPanggilFungsi();

      std::unique_ptr<Titik> uraiTempatParameterPanggilFungsi();

      std::unique_ptr<Titik> uraiAkhirDariFile();

      std::unique_ptr<Titik> uraiBilangan();
    // akhir dari access modifiers private
  
  }; // class PenguraiSintaks

} // namespace nusantara
