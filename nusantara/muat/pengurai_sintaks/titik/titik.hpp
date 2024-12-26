/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "pengurai_sintaks/titik/tipe_titik.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pendengar/a_pendengar_titik.hpp"
#include "token/token.hpp"

namespace nusantara {

  class Titik {
    public:
      Titik(Titik &&) = default;

      ~Titik() = default;

      Titik(const Titik& lainnya);

      Titik(const TipeTitik &tipe, const Token &token): tipe(tipe), token(token) {}

      explicit Titik(const TipeTitik &tipe) : tipe(tipe), token(std::nullopt) {}

      Titik & operator=(const Titik &) = default;

      Titik & operator=(Titik &&) = default;

      bool operator<(const Titik &lainnya) const;

      [[nodiscard]] const TipeTitik& ambilTipe() const;

      [[nodiscard]] const std::optional<nusantara::Token>& ambilToken() const;

      [[nodiscard]] const std::vector<std::unique_ptr<Titik>>& ambilKumpulanTitikTurunan() const;

      std::unique_ptr<Titik>&& keluarKanTitikTurunan(const size_t& index);

      template<typename T>
      auto terima(APengunjungTitik<T>& pengunjung) const -> T {
        switch (this->tipe) {
          case TipeTitik::AWAL:
              return pengunjung.kunjungiTitikAwal(*this);
          case TipeTitik::PERNYATAAN_EKSPRESI:
              return pengunjung.kunjungiTitikPernyataanEkspresi(*this);
          case TipeTitik::PANGGIL_FUNGSI:
              return pengunjung.kunjungiTitikPanggilFungsi(*this);
          case TipeTitik::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
              return pengunjung.kunjungiTitikTempatParameterPanggilFungsi(*this);
          case TipeTitik::TOKEN:
              return pengunjung.kunjungiTitikToken(*this);
          case TipeTitik::AKHIR_DARI_FILE:
              return pengunjung.kunjungiTitikAkhirDariFile(*this);
          default:
              std::cerr << "[Class Titik] Tipe titik tidak dapat di kunjungi." << std::endl;
              break;
        }
      }

      void terima(APendengarTitik& pendengar) const;

      void tambahTitikTurunan(std::unique_ptr<Titik> titik);
    // akhir dari access modifiers public
  
    private:
      TipeTitik tipe;
      std::optional<nusantara::Token> token;
      std::vector<std::unique_ptr<Titik>> kumpulanTitikTurunan;
    // akhir dari access modifiers private
  
  }; // class Titik

  void cetakTitik(const Titik &titik, int jarak);

}  // namespace nusantara