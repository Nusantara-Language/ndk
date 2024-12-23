#pragma once

#include "intruksi.hpp"
#include <memory>
#include <vector>

namespace nusantara {

  class Intruksi;

  class KumpulanIntruksi {
    public:
      KumpulanIntruksi();
      KumpulanIntruksi(std::vector<std::unique_ptr<Intruksi>>&& isinya);

      void jalankan();

      void tambahIntruksi(std::unique_ptr<Intruksi>&& intruksi);

    private:
      std::vector<std::unique_ptr<Intruksi>> isinya;
  };

}