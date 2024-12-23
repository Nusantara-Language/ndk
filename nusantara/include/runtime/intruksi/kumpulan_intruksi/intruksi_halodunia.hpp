#pragma once

#include "runtime/intruksi/intruksi.hpp"

namespace nusantara {

  class IntruksiHaloDunia: public Intruksi {
    public:
      IntruksiHaloDunia() = default;
      void jalankan() override;
  };

}
