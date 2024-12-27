/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef A_PENDENGAR_TITIK_HPP
#define A_PENDENGAR_TITIK_HPP

namespace nusantara {

  class Titik;

  class APendengarTitik {
    public:
      APendengarTitik() = default;

      APendengarTitik(const APendengarTitik &) = default;
      
      APendengarTitik(APendengarTitik &&) = default;

      virtual ~APendengarTitik() = default;

      APendengarTitik & operator=(const APendengarTitik &) = default;

      APendengarTitik & operator=(APendengarTitik &&) = default;

      virtual void awalMasuk(const Titik &titik) = 0;

      virtual void awalKeluar(const Titik &titik) = 0;

      virtual void pernyataanMasuk(const Titik &titik) = 0;

      virtual void pernyataanKeluar(const Titik &titik) = 0;

      virtual void panggilFungsiMasuk(const Titik &titik) = 0;

      virtual void panggilFungsiKeluar(const Titik &titik) = 0;

      virtual void tempatParameterPanggilFungsiMasuk(const Titik &titik) = 0;

      virtual void tempatParameterPanggilFungsiKeluar(const Titik &titik) = 0;

      virtual void tokenMasuk(const Titik &titik) = 0;

      virtual void tokenKeluar(const Titik &titik) = 0;

      virtual void akhirDariFileMasuk(const Titik &titik) = 0;

      virtual void akhirDariFileKeluar(const Titik &titik) = 0;

      virtual void bilanganMasuk(const Titik &titik) = 0;

      virtual void bilanganKeluar(const Titik &titik) = 0;
    // akhir dari access modifiers public

  }; // class APendengarTitik

} // namespace nusantara

#endif
