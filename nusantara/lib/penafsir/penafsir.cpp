/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <any>
#include <string>

#include "cetak/cetak.hpp"
#include "penafsir/penafsir.hpp"

void nusantara::Penafsir::kunjungiTitikToken(const Titik& titik)
{
  // Atur data sementara di runtime untuk menyimpan nama fungsi.
  if (titik.ambilToken())
    this->lingkunganEksekusi.aturDataSementara(titik.ambilToken()->konten);
} // function kunjungiTitikToken

void nusantara::Penafsir::kunjungiTitikAwal(const nusantara::Titik& titik)
{
  for (const auto& child : titik.ambilKumpulanTitikTurunan())
  {
    child->terima(*this);
  }
} // function kunjungiTitikAwalNode

void nusantara::Penafsir::kunjungiTitikPernyataan(const nusantara::Titik& titik)
{
  if (titik.ambilKumpulanTitikTurunan().size() > 0)
    titik.ambilKumpulanTitikTurunan()[0]->terima(*this);
} // function kunjungiTitikPernyataanNode

void nusantara::Penafsir::kunjungiTitikEkspresi(const nusantara::Titik& titik)
{
  cetakDBB(titik.ambilKumpulanTitikTurunan()[0]->ambilToken().value().konten);
} // function kunjungiTitikEkspresi

void nusantara::Penafsir::kunjungiTitikPanggilFungsi(const nusantara::Titik& node)
{
  // Pergi ke child index ke-0 untuk mendapatkan nama fungsi
  node.ambilKumpulanTitikTurunan()[0]->terima(*this);

  // Panggil fungsi sesuai nama
  this->lingkunganEksekusi.ambilBlokKode().ambilKumpulanFungsi().panggilFungsi(std::any_cast<std::string>(this->lingkunganEksekusi.ambilDataSementara()));
} // function kunjungiTitikPanggilFungsi