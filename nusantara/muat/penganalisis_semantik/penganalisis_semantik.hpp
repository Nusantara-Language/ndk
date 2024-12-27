/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PENGANALISIS_SEMANTIK_HPP
#define PENGANALISIS_SEMANTIK_HPP

#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"

namespace nusantara {

  class PenganalisisSemantik: public APengunjungTitik<void> {
    public:
      PenganalisisSemantik(): pengecualianSintaks() {}
    private:
      PengecualianSintaks pengecualianSintaks;
      void kunjungiTitikToken(const Titik &titik) override;
      void kunjungiTitikPanggilFungsi(const Titik &titik) override;
      void kunjungiTitikAwal(const Titik &titik) override;
      void kunjungiTitikTempatParameterPanggilFungsi(const Titik &titik) override;
      void kunjungiTitikPernyataan(const Titik &titik) override;
      void kunjungiTitikAkhirDariFile(const Titik &titik) override;
      void kunjungiTitikBilangan(const Titik &titik) override;
    // akhir dari access modifiers private

  }; // class PenganalisisSemantik

} // namespace nusantara

#endif
