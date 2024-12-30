/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PENGECUALIAN_SINTAKS_HPP
#define PENGECUALIAN_SINTAKS_HPP

#include <string>
#include <vector>

#include "pengecualian/antarmuka/a_pengecualian.h"
#include "token/token.hpp"

namespace nusantara {

struct DataPengecualianSintaks
{
  std::string lokasiBerkas;
  LokasiToken lokasiToken;
  std::string konten;
  std::string pesan;
}; // struct DataPengecualianSintaks

class PengecualianSintaks : public APengecualian
{
  public:
  PengecualianSintaks();

  PengecualianSintaks(const std::vector<DataPengecualianSintaks>& kumpulanData);

  PengecualianSintaks(const DataPengecualianSintaks& data);

  void perbaruiPesanSesuaiData();

  bool apaKahAdaData();

  void tambahData(const DataPengecualianSintaks& data);
  // akhir dari access modifiers public

  private:
  std::vector<DataPengecualianSintaks> kumpulanData;

  // akhir dari access modifiers private

  protected:
  // akhir dari access modifiers protected

}; // class PengecualianToken

} // namespace nusantara

#endif
