/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

namespace nusantara {

  class Titik;

  template<typename T> 
  class APengunjungTitik {
    public:
      APengunjungTitik<T>() = default;

      APengunjungTitik(const APengunjungTitik &) = default;

      APengunjungTitik(APengunjungTitik &&) = default;

      virtual ~APengunjungTitik() = default;

      APengunjungTitik & operator=(const APengunjungTitik &) = default;

      APengunjungTitik & operator=(APengunjungTitik &&) = default;

      virtual T kunjungiTitikAwal(const Titik& titik) = 0;

      virtual T kunjungiTitikPernyataanEkspresi(const Titik& titik) = 0;

      virtual T kunjungiTitikPanggilFungsi(const Titik& titik) = 0;

      virtual T kunjungiTitikTempatParameterPanggilFungsi(const Titik& titik) = 0;

      virtual T kunjungiTitikToken(const Titik& titik) = 0;

      virtual T kunjungiTitikAkhirDariFile(const Titik& titik) = 0;

      virtual T kunjungiTitikBilangan(const Titik& titik) = 0;
    // akhir dari access modifiers public

  }; // class APengunjungTitik
  
} // namespace nusantara