#pragma once

#include "kawasan/kawasan.hpp"
#include <any>

namespace nusantara {

  class Runtime {
    public:
      Runtime();

      Kawasan& ambilKawasan();

      std::any ambilDataSementara();
      void aturDataSementara(std::any nilai);
      void hapusDataSementara();

    private:
      std::any dataSementara;
      Kawasan kawasan;
  };

}