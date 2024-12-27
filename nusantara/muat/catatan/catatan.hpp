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
#include <iostream>

#ifdef __NK__CATATAN_AKTIF__

#ifdef __NK__CATATAN_SIMPAN_BERKAS__
#include <fstream>
#include <string>
#endif

#include "tipe_catatan.hpp"

#define __TEMPLATE__CATATAN_CETAK__(nama, tipe) \
      template<typename Type> \
      static void nama(const Type& pesan) { \
        Catatan::cetak(tipe, pesan); \
      } // function nama

#define __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(nama, tipe) \
      template<typename... Types> \
      static void nama(const Types&... kumpulanPesan) { \
        Catatan::cetak(tipe, (kumpulanPesan)...); \
      }

#define __TEMPLATE__CATATAN_CETAK_F__(nama, tipe) \
      template<typename... Types> \
      static void nama(const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) { \
        Catatan::cetakF(tipe, formatString, (kumpulanPesan)...); \
      }

namespace nusantara {

  class Catatan {
    public:
      // * DEBUG
      __TEMPLATE__CATATAN_CETAK__(debug, TipeCatatan::DEBUG)

      __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(debug, TipeCatatan::DEBUG)

      __TEMPLATE__CATATAN_CETAK_F__(debugF, TipeCatatan::DEBUG)

      // * INFO
      __TEMPLATE__CATATAN_CETAK__(info, TipeCatatan::INFO)

      __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(info, TipeCatatan::INFO)

      __TEMPLATE__CATATAN_CETAK_F__(infoF, TipeCatatan::INFO)

      // * PERINGATAN
      __TEMPLATE__CATATAN_CETAK__(peringatan, TipeCatatan::PERINGATAN)

      __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(peringatan, TipeCatatan::PERINGATAN)

      __TEMPLATE__CATATAN_CETAK_F__(peringatanF, TipeCatatan::PERINGATAN)

      // * KESALAHAN
      __TEMPLATE__CATATAN_CETAK__(kesalahan, TipeCatatan::KESALAHAN)

      __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(kesalahan, TipeCatatan::KESALAHAN)

      __TEMPLATE__CATATAN_CETAK_F__(kesalahanF, TipeCatatan::KESALAHAN)

      // * KESALAHAN FATAL
      __TEMPLATE__CATATAN_CETAK__(kesalahanFatal, TipeCatatan::KESALAHAN_FATAL)

      __TEMPLATE__CATATAN_CETAK_KUMPULAN_PESAN__(kesalahanFatal, TipeCatatan::KESALAHAN_FATAL)

      __TEMPLATE__CATATAN_CETAK_F__(kesalahanFatalF, TipeCatatan::KESALAHAN_FATAL)
    // akhir dari access modifiers public
  
    private:
      #ifdef __NK__CATATAN_SIMPAN_BERKAS__
      Catatan();
      ~Catatan();

      Catatan(const Catatan&) = delete;
      Catatan& operator=(const Catatan&) = delete;

      static inline Catatan* instance = nullptr;

      std::string lokasiFolder;
      std::string namaBerkas;
      std::string lokasiBerkas;

      static Catatan* ambilInstance();
      #endif

      template<typename Type>
      static void cetak(const TipeCatatan& tipe, const Type& pesan) {
        #if  defined(__NK__CATATAN_DEBUG__) \
          || defined(__NK__CATATAN_INFO__) \
          || defined(__NK__CATATAN_PERINGATAN__) \
          || defined(__NK__CATATAN_KESALAHAN__) \
          || defined(__NK__CATATAN_KESALAHAN_FATAL__)
        #ifdef __NK__CATATAN_SIMPAN_BERKAS__
        std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
        #endif
        switch (tipe) {
            #ifdef __NK__CATATAN_DEBUG__
            case DEBUG:
              #ifdef __NK__CATATAN_CETAK_DEBUG__
              std::cout << "\033[1;34m[CATATAN][DEBUG]\033[0m " << pesan << "\n";
              #endif
              #ifdef __NK__CATATAN_SIMPAN_BERKAS__
              file << "[CATATAN][DEBUG] " << pesan << "\n";
              #endif
              break;
            #endif
            #ifdef __NK__CATATAN_INFO__
            case INFO:
              #ifdef __NK__CATATAN_CETAK_INFO__
              std::cout << "\033[1;33m[CATATAN][INFO]\033[0m " << pesan << "\n";
              #endif
              #ifdef __NK__CATATAN_SIMPAN_BERKAS__
              file << "[CATATAN][INFO] " << pesan << "\n";
              #endif
              break;
            #endif
            #ifdef __NK__CATATAN_PERINGATAN__
            case PERINGATAN:
              #ifdef __NK__CATATAN_CETAK_PERINGATAN__
              std::cout << "\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m " << pesan << "\n";
              #endif
              #ifdef __NK__CATATAN_SIMPAN_BERKAS__
              file << "[CATATAN][PERINGATAN] " << pesan << "\n";
              #endif
              break;
            #endif
            #ifdef __NK__CATATAN_KESALAHAN__
            case KESALAHAN:
              #ifdef __NK__CATATAN_CETAK_KESALAHAN__
              std::cout << "\033[1;31m[CATATAN][KESALAHAN]\033[0m " << pesan << "\n";
              #endif
              #ifdef __NK__CATATAN_SIMPAN_BERKAS__
              file << "[CATATAN][KESALAHAN] " << pesan << "\n";
              #endif
              break;
            #endif
            #ifdef __NK__CATATAN_KESALAHAN_FATAL__
            case KESALAHAN_FATAL:
              #ifdef __NK__CATATAN_CETAK_KESALAHAN_FATAL__
              std::cout << "\033[0;31m[CATATAN][KESALAHAN_FATAL]\033[0m " << pesan << "\n";
              #endif
              #ifdef __NK__CATATAN_SIMPAN_BERKAS__
              file << "[CATATAN][KESALAHAN_FATAL] " << pesan << "\n";
              #endif
              break;
            #endif
          default:
            break;
        } // switch
        #endif
      } // function cetak

      template<typename... Types>
      static void cetak(const TipeCatatan& tipe, const Types&... kumpulanPesan) {
        #if  defined(__NK__CATATAN_DEBUG__) \
          || defined(__NK__CATATAN_INFO__) \
          || defined(__NK__CATATAN_PERINGATAN__) \
          || defined(__NK__CATATAN_KESALAHAN__) \
          || defined(__NK__CATATAN_KESALAHAN_FATAL__)
        #ifdef __NK__CATATAN_SIMPAN_BERKAS__
        std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
        #endif
        switch (tipe) {
          #ifdef __NK__CATATAN_DEBUG__
          case DEBUG:
            #ifdef __NK__CATATAN_CETAK_DEBUG__
            std::cout << "\033[1;34m[CATATAN][DEBUG]\033[0m ";
            ((std::cout << kumpulanPesan), ...);
            std::cout << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][DEBUG] ";
            ((file << kumpulanPesan), ...);
            file << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_INFO__
          case INFO:
            #ifdef __NK__CATATAN_CETAK_INFO__
            std::cout << "\033[1;33m[CATATAN][INFO]\033[0m ";
            ((std::cout << kumpulanPesan), ...);
            std::cout << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][INFO] ";
            ((file << kumpulanPesan), ...);
            file << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_PERINGATAN__
          case PERINGATAN:
            #ifdef __NK__CATATAN_CETAK_PERINGATAN__
            std::cout << "\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m ";
            ((std::cout << kumpulanPesan), ...);
            std::cout << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][PERINGATAN] ";
            ((file << kumpulanPesan), ...);
            file << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_KESALAHAN__
          case KESALAHAN:
            #ifdef __NK__CATATAN_CETAK_KESALAHAN__
            std::cout << "\033[1;31m[CATATAN][KESALAHAN]\033[0m ";
            ((std::cout << kumpulanPesan), ...);
            std::cout << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][KESALAHAN] ";
            ((file << kumpulanPesan), ...);
            file << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_KESALAHAN_FATAL__
          case KESALAHAN_FATAL:
            #ifdef __NK__CATATAN_CETAK_KESALAHAN_FATAL__
            std::cout << "\033[0;31m[CATATAN][KESALAHAN_FATAL]\033[0m ";
            ((std::cout << kumpulanPesan), ...);
            std::cout << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][KESALAHAN_FATAL] ";
            ((file << kumpulanPesan), ...);
            file << "\n";
            file.close();
            #endif
            break;
          #endif
          default:
            break;
        } // switch
        #endif
      }  // function cetak

      template<typename... Types>
      static void cetakF(const TipeCatatan& tipe, const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) {
        #if  defined(__NK__CATATAN_DEBUG__) \
          || defined(__NK__CATATAN_INFO__) \
          || defined(__NK__CATATAN_PERINGATAN__) \
          || defined(__NK__CATATAN_KESALAHAN__) \
          || defined(__NK__CATATAN_KESALAHAN_FATAL__)
        #ifdef __NK__CATATAN_SIMPAN_BERKAS__
        std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
        #endif
        switch (tipe) {
          #ifdef __NK__CATATAN_DEBUG__
          case DEBUG:
            #ifdef __NK__CATATAN_CETAK_DEBUG__
            std::cout << "\033[1;34m[CATATAN][DEBUG]\033[0m ";
            std::cout << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][DEBUG] ";
            file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_INFO__
          case INFO:
            #ifdef __NK__CATATAN_CETAK_INFO__
            std::cout << "\033[1;33m[CATATAN][INFO]\033[0m ";
            std::cout << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][INFO] ";
            file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_PERINGATAN__
          case PERINGATAN:
            #ifdef __NK__CATATAN_CETAK_PERINGATAN__
            std::cout << "\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m ";
            std::cout << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][PERINGATAN] ";
            file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_KESALAHAN__
          case KESALAHAN:
            #ifdef __NK__CATATAN_CETAK_KESALAHAN__
            std::cout << "\033[1;31m[CATATAN][KESALAHAN]\033[0m ";
            std::cout << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][KESALAHAN] ";
            file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            file.close();
            #endif
            break;
          #endif
          #ifdef __NK__CATATAN_KESALAHAN_FATAL__
          case KESALAHAN_FATAL:
            #ifdef __NK__CATATAN_CETAK_KESALAHAN_FATAL__
            std::cout << "\033[0;31m[CATATAN][KESALAHAN_FATAL]\033[0m ";
            std::cout << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            #endif
            #ifdef __NK__CATATAN_SIMPAN_BERKAS__
            file << "[CATATAN][KESALAHAN_FATAL] ";
            file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
            file.close();
            #endif
            break;
          #endif
          default:
            break;
        } // switch
        #endif
      }  // function cetak
    // akhir dari access modifiers private
  
  }; // class Catatan

} // namespace nusantara

#endif