/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "pengecualian/antarmuka/a_pengecualian.h"
#include "token/token.hpp"
#include <string>

namespace nusantara {

  class PengecualianSintaks: public APengecualian {
    public:
      PengecualianSintaks(const std::string& lokasiBerkas, const LokasiToken& lokasi, const std::string& konten, const std::string& pesan);
    // akhir dari access modifiers public
  
    private:
      std::string lokasiBerkas;
      std::string konten;
      LokasiToken lokasi;
    // akhir dari access modifiers private
  
    protected:
    // akhir dari access modifiers protected
  
  }; // class PengecualianToken

} // namespace nusantara