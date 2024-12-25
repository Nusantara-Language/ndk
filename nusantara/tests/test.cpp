/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "cetak/cetak.hpp"
#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"

int main() {
  nusantara::PengecualianSintaks test1(
    "contoh/main.n",
    {1, 17,},
    "3",
    "Error aja :)"
  );

  nusantara::PengecualianSintaks test2(
    "contoh/main.n",
    {1, 4,},
    "halodunia",
    "Error aja :)"
  );

  nstd::cetak(test1.ambilPesan());
  nstd::cetak(test2.ambilPesan());
  return 0;
}