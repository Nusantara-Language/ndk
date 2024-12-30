/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>
#include <optional>

#include "catatan/catatan.ap.hpp"
#include "pengecualian/antarmuka/a_pengecualian.h"
#include "pengurai_sintaks/titik/tipe_titik.hpp"
#include "pengurai_sintaks/titik/titik.hpp"
#include "token/tipe_token.hpp"

nusantara::Titik::Titik(const Titik& lainnya) : tipe(lainnya.tipe), token(lainnya.token)
{
  for (const auto& titikTurunan : lainnya.kumpulanTitikTurunan)
  {
    this->kumpulanTitikTurunan.push_back(std::make_unique<Titik>(*titikTurunan));
  }
} // constructor Titik

const nusantara::TipeTitik& nusantara::Titik::ambilTipe() const
{
  return this->tipe;
} // function ambilTipe

const std::optional<nusantara::Token>& nusantara::Titik::ambilToken() const
{
  return this->token;
} // function ambilToken

const std::vector<std::unique_ptr<nusantara::Titik>>& nusantara::Titik::ambilKumpulanTitikTurunan() const
{
  return this->kumpulanTitikTurunan;
} // function ambilKumpulanTitikTurunan

void nusantara::Titik::tambahTitikTurunan(std::unique_ptr<Titik> node)
{
  this->kumpulanTitikTurunan.push_back(std::move(node));
} // function tambahTitikTurunan

bool nusantara::Titik::operator<(const Titik& lainnya) const
{
  bool tokenBoolTemp = false;
  if (this->token && lainnya.token)
  {
    tokenBoolTemp = this->token->tipe < lainnya.token->tipe;
  }
  return this->tipe < lainnya.tipe && tokenBoolTemp && (this->kumpulanTitikTurunan.size() < lainnya.kumpulanTitikTurunan.size());
} // operator <

void nusantara::Titik::terima(APendengarTitik& pendengar) const
{
  switch (this->tipe)
  {
  case TipeTitik::TOKEN:
    pendengar.tokenMasuk(*this);
    break;
  case TipeTitik::AWAL:
    pendengar.awalMasuk(*this);
    break;
  case TipeTitik::PERNYATAAN:
    pendengar.pernyataanMasuk(*this);
    break;
  case TipeTitik::EKSPRESI:
    pendengar.ekspresiMasuk(*this);
    break;
  case TipeTitik::PANGGIL_FUNGSI:
    pendengar.panggilFungsiMasuk(*this);
    break;
  default:
    __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Class Titik"),
        "Tipe titik tidak dapat di dengar."); // __CATATAN__KESALAHAN_FATAL_M__
    break;
  } // switch

  for (const auto& child : this->ambilKumpulanTitikTurunan())
  {
    child->terima(pendengar);
  } // for

  switch (this->tipe)
  {
  case TipeTitik::TOKEN:
    pendengar.tokenKeluar(*this);
    break;
  case TipeTitik::AWAL:
    pendengar.awalKeluar(*this);
    break;
  case TipeTitik::PERNYATAAN:
    pendengar.pernyataanKeluar(*this);
    break;
  case TipeTitik::EKSPRESI:
    pendengar.ekspresiKeluar(*this);
    break;
  case TipeTitik::PANGGIL_FUNGSI:
    pendengar.panggilFungsiKeluar(*this);
    break;
  default:
    __CATATAN__KESALAHAN_FATAL_M__(__NK__LABEL_KELUARAN_CUSTOM__("Class Titik"),
        "Tipe titik tidak dapat di dengar."); // __CATATAN__KESALAHAN_FATAL_M__
    break;
  } // switch

} // function terima

void nusantara::cetakTitik(const Titik& titik, int jarak)
{
  if (titik.ambilTipe() != TipeTitik::TOKEN && titik.ambilToken() == std::nullopt)
  {
    std::cout << "\033[34m[" << tipeTitikKeString(titik.ambilTipe()) << "]\033[0m\n";
  } // if

  if (titik.ambilToken())
  {
    std::cout << nusantara::tipeTokenKeString(titik.ambilToken()->tipe) << ": \033[33m" << titik.ambilToken()->konten << "\033[0m\n";
  } // if

  jarak += 3;

  for (const auto& titikTurunan : titik.ambilKumpulanTitikTurunan())
  {
    std::cout << std::string(jarak, ' ') << "\033[32m|\033[0m\n";
    std::cout << std::string(jarak, ' ') << "\033[32m->\033[0m";
    cetakTitik(*titikTurunan, jarak);
  } // for

} // function cetakTitik

std::unique_ptr<nusantara::Titik>&& nusantara::Titik::keluarKanTitikTurunan(const size_t& index)
{
  if (index >= this->kumpulanTitikTurunan.size() || index < 0)
  {
    throw APengecualian(__NK__LABEL_KELUARAN_CUSTOM__("Class Titik") "kesalahan, karena mencoba mengeluarkan titik turunan dengan indeks diluar kapasitas titik turunan.");
  } // if

  return std::move(this->kumpulanTitikTurunan[index]);
} // function keluarKanTitikTurunan

void nusantara::Titik::aturToken(const Token& token)
{
  this->token = token;
} // function aturToken

void nusantara::Titik::pindahKanSemuaTitikTurunanKe(Titik& titik)
{
  for (auto& titikTuruanan : this->kumpulanTitikTurunan)
  {
    titik.tambahTitikTurunan(std::move(titikTuruanan));
  }
} // function pindahKanSemuaTitikTurunanKe

void nusantara::Titik::hapusAkhirDariBerkasJikaAda()
{
  if (this->kumpulanTitikTurunan.empty())
    return;
  if (this->kumpulanTitikTurunan.back()->tipe != TipeTitik::TOKEN)
    return;
  if (this->kumpulanTitikTurunan.back()->token->tipe == TipeToken::akhirDariFile)
  {
    this->kumpulanTitikTurunan.pop_back();
  } // if
} // hapusAkhirDariFileJikaAda