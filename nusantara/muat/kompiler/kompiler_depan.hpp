/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef KOMPILER_DEPAN_HPP
#define KOMPILER_DEPAN_HPP

#include "penganalisis_semantik/penganalisis_semantik.hpp"
#include "pengurai_sintaks/pengurai_sintaks.hpp"
#include "pemecah_sintaks/pemecah_sintaks.hpp"
#include "pengurai_sintaks/titik/titik.hpp"
#include "token/token.hpp"
#include <variant>
#include <vector>

namespace nusantara {

  class KompilerDepan {
    public:
      KompilerDepan();

      void aturUlang();
      const Titik& ambilHasil();
    // akhir dari access modifiers public
  
    private:
      PemecahSintaks pemecah;
      PenguraiSintaks pengurai;
      PenganalisisSemantik analisisSemantic;
      std::variant<Titik, std::vector<Token>> hasil;
    // akhir dari access modifiers private
  
    protected:
    // akhir dari access modifiers protected
  
  }; // class KompilerDepan

} // namespace nusantara

#endif