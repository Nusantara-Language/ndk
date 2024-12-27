/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef KUMPULAN_INTRUKSI_HPP
#define KUMPULAN_INTRUKSI_HPP

#include "intruksi.hpp"
#include <memory>
#include <vector>

namespace nusantara {

  class Intruksi;

  class KumpulanIntruksi {
    public:
      KumpulanIntruksi();
      
      KumpulanIntruksi(std::vector<std::unique_ptr<Intruksi>>&& isinya);

      void jalankan();

      void tambahIntruksi(std::unique_ptr<Intruksi>&& intruksi);
    // akhir dari access modifiers public

    private:
      std::vector<std::unique_ptr<Intruksi>> isinya;
    // akhir dari access modifiers private

  }; // class KumpulanIntruksi

} // namespace nusantara

#endif
