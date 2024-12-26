/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include <format>
#include <string>
#include <vector>

#include "pengecualian/kumpulan_pengecualian/pengecualian_sintaks.hpp"
#include "pengecualian/antarmuka/a_pengecualian.h"
#include "konfig/konfig_label_keluaran.hpp"
#include "token/token.hpp"
#include "alat.hpp"

nusantara::PengecualianSintaks::PengecualianSintaks(): PengecualianSintaks(std::vector<DataPengecualianSintaks>{}) {} // constructor PengecualianSintaks

nusantara::PengecualianSintaks::PengecualianSintaks(
  const std::vector<DataPengecualianSintaks>& kumpulanData
): APengecualian( __NK__LABEL_KELUARAN_CUSTOM("Class PengecualianSintaks") "Pesan pengecualian belum dibuat."), kumpulanData(kumpulanData) {} // constructor PengecualianSintaks

nusantara::PengecualianSintaks::PengecualianSintaks(
  const DataPengecualianSintaks& data
): PengecualianSintaks(std::vector<DataPengecualianSintaks>{data}) {} // constructor PengecualianSintaks

void nusantara::PengecualianSintaks::perbaruiPesanSesuaiData() {
  std::string lokasiBerkasSebelumnya;
  std::vector<std::string> kontenBerkas;
  LokasiToken lokasiTokenSebelumnya{0, 0};
  std::string kontenSebelumnya;
  std::string pesanSebelumnya;

  // Hasil akhir
  std::string hasil;

  // Fungsi untuk mencetak pesan ke hasil
  auto cetakPesan = [&](const std::string& lokasiBerkas, const LokasiToken& lokasiToken, const std::string& konten, const std::string& pesan) {
    if (pesan.empty()) return;

    // Format lokasi, baris kode, dan panah
    std::string prefix = std::format("{}| ", lokasiToken.baris);
    int jarakPanah = prefix.size() + lokasiToken.kolom - 1;

    hasil += "---------------------------------------------\n";
    hasil += std::format("{}:{}:{}\n\n", lokasiBerkas, lokasiToken.baris, lokasiToken.kolom);
    hasil += std::format("{}{}\n", prefix, kontenBerkas[lokasiToken.baris - 1]);
    hasil += std::format("{}{}\n", std::string(jarakPanah, ' '), std::string(std::max(1, static_cast<int>(konten.size())), '^'));
    hasil += pesan + "\n\n";
  };

  // Iterasi melalui kumpulan data
  for (const auto& data : this->kumpulanData) {
    // Jika file berubah, cetak pesan sebelumnya dan reset
    if (lokasiBerkasSebelumnya != data.lokasiBerkas) {
      cetakPesan(lokasiBerkasSebelumnya, lokasiTokenSebelumnya, kontenSebelumnya, pesanSebelumnya);
      lokasiBerkasSebelumnya = data.lokasiBerkas;
      kontenBerkas = nusantara::pisahkanStringDenganPembatas(nusantara::bacaBerkasDalamBentukString(lokasiBerkasSebelumnya), '\n');
      lokasiTokenSebelumnya = data.lokasiToken;
      kontenSebelumnya = data.konten;
      pesanSebelumnya = data.pesan;
      continue;
    }

    // Jika pada baris yang sama dan pesan yang sama, gabungkan panah
    if (lokasiTokenSebelumnya.baris == data.lokasiToken.baris && pesanSebelumnya == data.pesan) {
      int panjangTambahan = data.lokasiToken.kolom - (lokasiTokenSebelumnya.kolom + kontenSebelumnya.size());
      kontenSebelumnya += std::string(std::max(0, panjangTambahan), ' ') + data.konten;
    } 
    // Jika pesan berbeda, cetak pesan sebelumnya dan mulai baru
    else {
      cetakPesan(lokasiBerkasSebelumnya, lokasiTokenSebelumnya, kontenSebelumnya, pesanSebelumnya);
      lokasiTokenSebelumnya = data.lokasiToken;
      kontenSebelumnya = data.konten;
      pesanSebelumnya = data.pesan;
    }
  }

  // Cetak pesan terakhir
  cetakPesan(lokasiBerkasSebelumnya, lokasiTokenSebelumnya, kontenSebelumnya, pesanSebelumnya);

  // Trim hasil dan simpan
  this->pesan = nusantara::hapusRuangKosongDiAwalDanAkhirString(hasil);
} // function perbaruiPesanSesuaiData

bool nusantara::PengecualianSintaks::apaKahAdaData() {
  return !this->kumpulanData.empty();
}

void nusantara::PengecualianSintaks::tambahData(const DataPengecualianSintaks& data) {
  this->kumpulanData.push_back(data);
}