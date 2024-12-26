/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "pengunjung/a_pengunjung_titik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"

namespace nusantara {

  class PenganalisisSemantik: public APengunjungTitik<bool> {
    private:
      bool kunjungiTitikToken(const Titik &titik) override;
      bool kunjungiTitikPanggilFungsi(const Titik &titik) override;
      bool kunjungiTitikAwal(const Titik &titik) override;
      bool kunjungiTitikTempatParameterPanggilFungsi(const Titik &titik) override;
      bool kunjungiTitikPernyataanEkspresi(const Titik &titik) override;
      bool kunjungiTitikAkhirDariFile(const Titik &titik) override;
    // akhir dari access modifiers private

  }; // class PenganalisisSemantik

} // namespace nusantara