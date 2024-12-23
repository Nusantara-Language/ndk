#include "runtime/fungsi/kumpulan_fungsi.hpp"
#include "cetak/cetak.hpp"
#include <algorithm>
#include <string>
#include <vector>

nusantara::KumpulanFungsi::KumpulanFungsi(): isinya() {}

nusantara::KumpulanFungsi::KumpulanFungsi(std::vector<std::unique_ptr<IFungsi>>&& isinya): isinya(std::move(isinya)) {}

void nusantara::KumpulanFungsi::panggilFungsi(const std::string& nama) {
  auto fungsi = std::find_if(this->isinya.begin(), this->isinya.end(), [nama](const std::unique_ptr<IFungsi>& fungsi) { return fungsi->ambilNama() == nama; });

  if(fungsi != this->isinya.end()) {
    (*fungsi)->panggil();
    return;
  }

  nstd::cetakDBBDF("[RT] Fungsi '{}' tidak ada.", nama);
}

void nusantara::KumpulanFungsi::tambahFungsi(std::unique_ptr<IFungsi>&& intruksi) {
  this->isinya.push_back(std::move(intruksi));
}