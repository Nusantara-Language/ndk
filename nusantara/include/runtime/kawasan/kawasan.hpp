#pragma once

#include "runtime/intruksi/kumpulan_intruksi.hpp"
#include "runtime/fungsi/kumpulan_fungsi.hpp"

namespace nusantara {

  class Kawasan {
    public:
      Kawasan(
        KumpulanFungsi &&kumpulanFungsi,
        KumpulanIntruksi &&kumpulanIntruksi
      );

      KumpulanIntruksi& ambilKumpulanIntruksi();
      KumpulanFungsi& ambilKumpulanFungsi();

    private:
      KumpulanIntruksi kumpulanIntruksi;
      KumpulanFungsi kumpulanFungsi;
  };

}