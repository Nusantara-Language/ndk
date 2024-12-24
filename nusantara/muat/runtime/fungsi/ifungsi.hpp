#pragma once

#include <string>

namespace nusantara {

  class IFungsi {
    public:
      virtual ~IFungsi() = default;
      virtual void panggil() = 0;
      virtual const std::string& ambilNama() = 0;
  };

}