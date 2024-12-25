/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <exception>
#include <string>

namespace nusantara {

  class APengecualian : public std::exception {
    public:
      virtual ~APengecualian() = default;
      explicit APengecualian(const std::string& pesan) : pesan(pesan) {}
      
      const char* what() const noexcept override;
      
      const std::string& ambilPesan();
    // akhir dari access modifiers public
  
    private:
    // akhir dari access modifiers private
  
    protected:
      std::string pesan;
    // akhir dari access modifiers protected
  
  }; // class APengecualian

} // namespace nusantara