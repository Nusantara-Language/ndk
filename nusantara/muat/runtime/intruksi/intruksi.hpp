#pragma once

namespace nusantara {

  class Intruksi {
    public:
      virtual ~Intruksi() = default;  // Menambahkan default destructor
      virtual void jalankan() = 0;
    private:
  };

}