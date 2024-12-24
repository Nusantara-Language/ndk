#include "runtime/intruksi/kumpulan_intruksi.hpp"

nusantara::KumpulanIntruksi::KumpulanIntruksi(): isinya() {}

nusantara::KumpulanIntruksi::KumpulanIntruksi(
  std::vector<std::unique_ptr<Intruksi>>&& isinya
): isinya(std::move(isinya)) {}

void nusantara::KumpulanIntruksi::jalankan() {
  for(const auto& intruksi: this->isinya) {
    if(intruksi != nullptr) {
      intruksi->jalankan();
    }
  }
}

void nusantara::KumpulanIntruksi::tambahIntruksi(std::unique_ptr<Intruksi>&& intruksi) {
  this->isinya.push_back(std::move(intruksi));
}
