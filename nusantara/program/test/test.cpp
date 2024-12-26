#include "cetak/cetak.hpp"
#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include <vector>

int main() {

  nusantara::PengecualianSintaks kumpulanPengecualianSintaks{
    std::vector<nusantara::DataPengecualianSintaks>(
      {
        {
          "contoh/main.n",
          {1, 1},
          "(",
          "Masa iya kurung bulat :v"
        },
        {
          "contoh/main.n",
          {1, 11},
          ";",
          "Masa iya kurung bulat :v"
        },
        {
          "contoh/main.n",
          {2, 4},
          "saya",
          "Masa iya kurung bulat :v"
        },
        {
          "contoh/main.n",
          {2, 12},
          "Aerell",
          "Apa aerell? :v"
        },
        {
          "contoh/main.n",
          {4, 9},
          "Gak",
          "Masa Gak?"
        },
        {
          "contoh/main.n",
          {4, 20},
          "Dih gila",
          "Masa Gak?"
        },
        {
          "contoh/main.n",
          {6, 6},
          "Gak()",
          "Masa Gak?"
        }
      }
    )
  };

  kumpulanPengecualianSintaks.perbaruiPesanSesuaiData();
  nusantara::cetakDBB(kumpulanPengecualianSintaks.what());

  return 0;
}