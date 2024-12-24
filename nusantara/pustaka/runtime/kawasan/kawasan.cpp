#include "runtime/kawasan/kawasan.hpp"
#include "runtime/fungsi/kumpulan_fungsi.hpp"
#include "runtime/intruksi/kumpulan_intruksi.hpp"

nusantara::Kawasan::Kawasan(
  KumpulanFungsi &&kumpulanFungsi,
  KumpulanIntruksi &&kumpulanIntruksi
): 
kumpulanIntruksi(std::move(kumpulanIntruksi)), 
kumpulanFungsi(std::move(kumpulanFungsi)) 
{}

nusantara::KumpulanIntruksi& nusantara::Kawasan::ambilKumpulanIntruksi() {
  return this->kumpulanIntruksi;
}

nusantara::KumpulanFungsi& nusantara::Kawasan::ambilKumpulanFungsi() {
  return this->kumpulanFungsi;
}