#include "runtime/fungsi/kumpulan_fungsi/fungsi_halodunia.hpp"
#include "runtime/fungsi/fungsi.hpp"
#include "runtime/intruksi/kumpulan_intruksi/intruksi_halodunia.hpp"
#include "runtime/kawasan/kawasan.hpp"
#include <memory>

nusantara::FungsiHaloDunia::FungsiHaloDunia(): Fungsi("halodunia")  {
  this->kawasan.ambilKumpulanIntruksi()
    .tambahIntruksi(std::move(std::make_unique<IntruksiHaloDunia>()));
}

