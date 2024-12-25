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
#include "lingkungan_eksekusi/lingkungan_eksekusi.hpp"

namespace nusantara {

  class Penafsir: public APengunjungTitik<void> {
    private:
      LingkunganEksekusi lingkunganEksekusi;
      void kunjungiTitikAwal(const Titik &titik) override;
      void kunjungiTitikPanggilFungsi(const Titik &titik) override;
      void kunjungiTitikTempatParameterPanggilFungsi(const Titik &titik) override;
      void kunjungiTitikPernyataanEkspresi(const Titik &titik) override;
      void kunjungiTitikToken(const Titik &titik) override;
    // akhir dari access modifies private

  }; // class Penafsir

} // namespace nusantara