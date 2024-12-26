/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <algorithm>
#include <string>
#include <vector>

#include "lingkungan_eksekusi/fungsi/kumpulan_fungsi.hpp"
#include "konfig/konfig_label_keluaran.hpp"
#include "cetak/cetak.hpp"

nusantara::KumpulanFungsi::KumpulanFungsi(): isinya() {}

nusantara::KumpulanFungsi::KumpulanFungsi(std::vector<std::unique_ptr<AFungsi>>&& isinya): isinya(std::move(isinya)) {}

void nusantara::KumpulanFungsi::panggilFungsi(const std::string& nama) {
  auto fungsi = std::find_if(this->isinya.begin(), this->isinya.end(), [nama](const std::unique_ptr<AFungsi>& fungsi) { return fungsi->ambilNama() == nama; });

  if(fungsi != this->isinya.end()) {
    (*fungsi)->panggil();
    return;
  } // if

  nusantara::cetakDBBDF(__NK__LABEL_KELUARAN_LE "Fungsi '{}' tidak ada.", nama);
} // function panggilFungsi

void nusantara::KumpulanFungsi::tambahFungsi(std::unique_ptr<AFungsi>&& intruksi) {
  this->isinya.push_back(std::move(intruksi));
} // function tambahFungsi