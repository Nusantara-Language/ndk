/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "token/token.hpp"
#include "alat.hpp"

#include <algorithm>
#include <format>
#include <string>
#include <variant>
#include <vector>

nusantara::PengecualianSintaks::PengecualianSintaks(
  const std::string& lokasiBerkas, 
  const LokasiToken& lokasi, 
  const std::string& konten,
  const std::string& pesan
): APengecualian(pesan), lokasiBerkas(lokasiBerkas), lokasi(lokasi), konten(konten) {
  /**
   * @brief Format pesan kesalahan yang akan muuncul di terminal
   * 
   * @code {terminal}
   * main.n:5:10
   *
   * 1| halodunia-=();
   *             ^
   * Karakter tidak di kenali.
   * @endcode
   */
  std::variant<std::string, std::vector<std::string>> kontenBerkas = nstd::bacaBerkasDalamBentukString(lokasiBerkas);
  kontenBerkas = nstd::pisahkanStringDenganPembatas(std::get<std::string>(kontenBerkas), '\n');
  const std::vector<std::string>& kontenBerkasVector = std::get<std::vector<std::string>>(kontenBerkas);

  std::string prefix = std::format("{}| ", this->lokasi.baris);
  int jarakPanah = prefix.size() + this->lokasi.kolom - 1;

  std::string pesanBaru = std::format("{}:{}:{}\n\n", this->lokasiBerkas, this->lokasi.baris, this->lokasi.kolom);
  pesanBaru += std::format("{}{}\n", prefix, kontenBerkasVector[(this->lokasi.baris - 1) > (kontenBerkasVector.size() - 1) ? (kontenBerkasVector.size() - 1) : (this->lokasi.baris - 1)]);
  pesanBaru += std::format("{}{}\n", std::string(jarakPanah, ' '), std::string(this->konten.size(), '^'));
  pesanBaru += std::format("{}{}\n\n", std::string(std::max(0, jarakPanah + (static_cast<int>(this->konten.size()) - 1) - (static_cast<int>(this->pesan.size()) - 1) / 2) - (static_cast<int>(this->konten.size() - 1) / 2), ' '), this->pesan);

  this->pesan = pesanBaru;
} // constructor PengecualianSintaks