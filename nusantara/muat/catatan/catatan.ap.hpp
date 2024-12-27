/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include "konfig/konfig_catatan.hpp"

#ifdef __NK__CATATAN_AKTIF__

  #include "catatan.hpp"

  #define __CATATAN__DEBUG__(pesan) nusantara::Catatan::debug(pesan)

  #define __CATATAN__DEBUG_M__(pesan, ...) nusantara::Catatan::debug(pesan, __VA_ARGS__)

  #define __CATATAN__DEBUG_F__(pesan, ...) nusantara::Catatan::debugF(pesan, __VA_ARGS__)

  #define __CATATAN__INFO__(pesan) nusantara::Catatan::info(pesan)

  #define __CATATAN__INFO_M__(pesan, ...) nusantara::Catatan::info(pesan, __VA_ARGS__)

  #define __CATATAN__INFO_F__(pesan, ...) nusantara::Catatan::infoF(pesan, __VA_ARGS__)

  #define __CATATAN__PERINGATAN__(pesan) nusantara::Catatan::peringatan(pesan)

  #define __CATATAN__PERINGATAN_M__(pesan, ...) nusantara::Catatan::peringatan(pesan, __VA_ARGS__)

  #define __CATATAN__PERINGATAN_F__(pesan, ...) nusantara::Catatan::peringatanF(pesan, __VA_ARGS__)

  #define __CATATAN__KESALAHAN__(pesan) nusantara::Catatan::kesalahan(pesan)

  #define __CATATAN__KESALAHAN_M__(pesan, ...) nusantara::Catatan::kesalahan(pesan, __VA_ARGS__)

  #define __CATATAN__KESALAHAN_F__(pesan, ...) nusantara::Catatan::kesalahanF(pesan, __VA_ARGS__)

  #define __CATATAN__KESALAHAN_FATAL__(pesan) nusantara::Catatan::kesalahanFatal(pesan)

  #define __CATATAN__KESALAHAN_FATAL_M__(format, ...) nusantara::Catatan::kesalahanFatal(format, __VA_ARGS__)

  #define __CATATAN__KESALAHAN_FATAL_F__(format, ...) nusantara::Catatan::kesalahanFatalF(format, __VA_ARGS__)

#else

  #define __CATATAN__DEBUG__(pesan)

  #define __CATATAN__DEBUG_M__(pesan, ...)

  #define __CATATAN__DEBUG_F__(pesan, ...)

  #define __CATATAN__INFO__(pesan)

  #define __CATATAN__INFO_M__(pesan, ...)

  #define __CATATAN__INFO_F__(pesan, ...)

  #define __CATATAN__PERINGATAN__(pesan)

  #define __CATATAN__PERINGATAN_M__(pesan, ...)

  #define __CATATAN__PERINGATAN_F__(pesan, ...)

  #define __CATATAN__KESALAHAN__(pesan)

  #define __CATATAN__KESALAHAN_M__(pesan, ...)

  #define __CATATAN__KESALAHAN_F__(pesan, ...)

  #define __CATATAN__KESALAHAN_FATAL__(pesan)

  #define __CATATAN__KESALAHAN_FATAL_M__(format, ...)

  #define __CATATAN__KESALAHAN_FATAL_F__(format, ...)

#endif