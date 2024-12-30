/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef TITIK_HPP
#define TITIK_HPP

#include <optional>
#include <vector>

#include "catatan/catatan.ap.hpp"
#include "konfig/konfig_label_keluaran.hpp"
#include "pendengar/a_pendengar_titik.hpp"
#include "pengunjung/a_pengunjung_titik.hpp"
#include "pengurai_sintaks/titik/tipe_titik.hpp"
#include "token/token.hpp"

namespace nusantara {

class Titik
{
  public:
  Titik(Titik&&) = default;

  ~Titik() = default;

  Titik(const Titik& lainnya);

  Titik(const TipeTitik& tipe, const Token& token) : tipe(tipe), token(token) {}

  explicit Titik(const TipeTitik& tipe) : tipe(tipe), token(std::nullopt) {}

  Titik& operator=(const Titik&) = default;

  Titik& operator=(Titik&&) = default;

  bool operator<(const Titik& lainnya) const;

  [[nodiscard]] const TipeTitik& ambilTipe() const;

  [[nodiscard]] const std::optional<nusantara::Token>& ambilToken() const;

  [[nodiscard]] const std::vector<std::unique_ptr<Titik>>& ambilKumpulanTitikTurunan() const;

  std::unique_ptr<Titik>&& keluarKanTitikTurunan(const size_t& index);

  void aturToken(const Token& token);

  template <typename T>
  auto terima(APengunjungTitik<T>& pengunjung) const -> T
  {
    switch (this->tipe)
    {
    case TipeTitik::TOKEN:
      return pengunjung.kunjungiTitikToken(*this);
    case TipeTitik::AWAL:
      return pengunjung.kunjungiTitikAwal(*this);
    case TipeTitik::PERNYATAAN:
      return pengunjung.kunjungiTitikPernyataan(*this);
    case TipeTitik::EKSPRESI:
      return pengunjung.kunjungiTitikEkspresi(*this);
    case TipeTitik::PANGGIL_FUNGSI:
      return pengunjung.kunjungiTitikPanggilFungsi(*this);
    default:
      __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Class Titik"),
          "Tipe titik tidak dapat di kunjungi."); // __CATATAN__KESALAHAN_FATAL_M__
      break;
    }
  }

  void terima(APendengarTitik& pendengar) const;

  void tambahTitikTurunan(std::unique_ptr<Titik> titik);

  void pindahKanSemuaTitikTurunanKe(Titik& titik);

  void hapusAkhirDariBerkasJikaAda();
  // akhir dari access modifiers public

  private:
  TipeTitik tipe;
  std::optional<nusantara::Token> token;
  std::vector<std::unique_ptr<Titik>> kumpulanTitikTurunan;
  // akhir dari access modifiers private

}; // class Titik

void cetakTitik(const Titik& titik, int jarak);

} // namespace nusantara

#endif
