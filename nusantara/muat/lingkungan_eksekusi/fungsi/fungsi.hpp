/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef FUNGSI_HPP
#define FUNGSI_HPP

#include "lingkungan_eksekusi/blok_kode/blok_kode.hpp"
#include "antarmuka/a_fungsi.hpp"
#include <string>

namespace nusantara {

  class Fungsi: public AFungsi {
    public:
      Fungsi(const std::string& nama);
      
      Fungsi(const std::string& nama, BlokKode&& blokKode);

      void panggil() override;

      const std::string& ambilNama() override;
    // akhir dari access modifiers public

    private:
      std::string nama;
    // akhir dari access modifiers private

    protected:
      BlokKode blokKode;
    // akhir dari access modifiers protected

  }; // class Fungsi

} // namespace nusantara

#endif
