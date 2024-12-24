#pragma once

#include "ifungsi.hpp"
#include "runtime/kawasan/kawasan.hpp"
#include <string>

namespace nusantara {

  class Fungsi: public IFungsi {
    public:
      Fungsi(const std::string& nama);
      Fungsi(const std::string& nama, Kawasan&& kawasan);

      void panggil() override;
      const std::string& ambilNama() override;

    private:
      std::string nama;
    protected:
      Kawasan kawasan;
  };

}