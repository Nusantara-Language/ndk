#pragma once

#include "runtime/fungsi/ifungsi.hpp"
#include <memory>
#include <string>
#include <vector>

namespace nusantara {

  class KumpulanFungsi {
    public:
      KumpulanFungsi();
      KumpulanFungsi(std::vector<std::unique_ptr<IFungsi>>&& isinya);

      void panggilFungsi(const std::string& nama);
      void tambahFungsi(std::unique_ptr<IFungsi>&& intruksi);

    private:
      std::vector<std::unique_ptr<IFungsi>> isinya;
  };

}