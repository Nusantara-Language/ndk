#include "runtime/runtime.hpp"
#include "runtime/fungsi/kumpulan_fungsi/fungsi_halodunia.hpp"
#include "runtime/kawasan/kawasan.hpp"
#include <any>
#include <memory>
#include <utility>

nusantara::Runtime::Runtime(): kawasan({}, {}) {
  // Inisialisasi
  this->kawasan.ambilKumpulanFungsi().tambahFungsi(std::move(std::make_unique<FungsiHaloDunia>()));
}

nusantara::Kawasan& nusantara::Runtime::ambilKawasan() {
  return this->kawasan;
}

std::any nusantara::Runtime::ambilDataSementara() {
  return this->dataSementara;
}

void nusantara::Runtime::aturDataSementara(std::any nilai) {
  this->dataSementara = std::move(nilai);
}

void nusantara::Runtime::hapusDataSementara() {
  this->dataSementara.reset();
}
