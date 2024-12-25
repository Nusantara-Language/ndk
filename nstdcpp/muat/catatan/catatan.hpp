/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <fstream>
#include <string>

#include "tipe_catatan.hpp"
#include "cetak/cetak.hpp"

namespace nstd {

  class Catatan {
    public:
      // * INFO
      template<typename Type>
      static void info(const Type& pesan) {
        Catatan::cetak(TipeCatatan::INFO, pesan);
      } // function info

      template<typename... Types>
      static void info(const Types&... kumpulanPesan) {
        Catatan::cetak(TipeCatatan::INFO, (kumpulanPesan)...);
      }

      template<typename... Types>
      static void infoF(const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) {
        Catatan::cetakF(TipeCatatan::INFO, formatString, (kumpulanPesan)...);
      } // function info

      // * PERINGATAN
      template<typename Type>
      static void peringatan(const Type& pesan) {
        Catatan::cetak(TipeCatatan::PERINGATAN, pesan);
      } // function peringatan

      template<typename... Types>
      static void peringatan(const Types&... kumpulanPesan) {
        Catatan::cetak(TipeCatatan::PERINGATAN, (kumpulanPesan)...);
      }

      template<typename... Types>
      static void peringatanF(const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) {
        Catatan::cetakF(TipeCatatan::PERINGATAN, formatString, (kumpulanPesan)...);
      } // function peringatan

      // * KESALAHAN
      template<typename Type>
      static void kesalahan(const Type& pesan) {
        Catatan::cetak(TipeCatatan::KESALAHAN, pesan);
      } // function kesalahan

      template<typename... Types>
      static void kesalahan(const Types&... kumpulanPesan) {
        Catatan::cetak(TipeCatatan::KESALAHAN, (kumpulanPesan)...);
      }

      template<typename... Types>
      static void kesalahanF(const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) {
        Catatan::cetakF(TipeCatatan::KESALAHAN, formatString, (kumpulanPesan)...);
      } // function kesalahan
    // akhir dari access modifiers public
  
    private:
      Catatan();
      ~Catatan();

      Catatan(const Catatan&) = delete;
      Catatan& operator=(const Catatan&) = delete;

      static inline Catatan* instance = nullptr;

      std::string lokasiFolder;
      std::string namaBerkas;
      std::string lokasiBerkas;

      static Catatan* ambilInstance();

      template<typename Type>
      static void cetak(const TipeCatatan& tipe, const Type& pesan) {
        switch (tipe) {
            case INFO:
              nstd::cetak("\033[1;33m[CATATAN][INFO]\033[0m ");
              break;
            case PERINGATAN:
              nstd::cetak("\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m ");
              break;
            case KESALAHAN:
              nstd::cetak("\033[1;31m[CATATAN][KESALAHAN]\033[0m ");
              break;
          default:
            break;
        } // switch
        switch (tipe) {
          case INFO:
          case PERINGATAN:
          case KESALAHAN:
            nstd::cetakDBB(pesan);
              std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
              switch (tipe) {
                case INFO:
                  file << "[CATATAN][INFO] " << pesan << "\n";
                  break;
                case PERINGATAN:
                  file << "[CATATAN][PERINGATAN] " << pesan << "\n";
                  break;
                case KESALAHAN:
                  file << "[CATATAN][KESALAHAN] " << pesan << "\n";
                  break;
                default:
                  break;
              } // switch
              file.close();
            break;
        } // switch
      } // function cetak

      template<typename... Types>
      static void cetak(const TipeCatatan& tipe, const Types&... kumpulanPesan) {
        switch (tipe) {
          case INFO:
            nstd::cetak("\033[1;33m[CATATAN][INFO]\033[0m ");
            break;
          case PERINGATAN:
            nstd::cetak("\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m ");
            break;
          case KESALAHAN:
            nstd::cetak("\033[1;31m[CATATAN][KESALAHAN]\033[0m ");
            break;
          default:
            break;
        } // switch
        switch (tipe) {
          case INFO:
          case PERINGATAN:
          case KESALAHAN:
            (nstd::cetak(kumpulanPesan), ...);
            nstd::cetak("\n");
              std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
              switch (tipe) {
                case INFO:
                  file << "[CATATAN][INFO] ";
                  break;
                case PERINGATAN:
                  file << "[CATATAN][PERINGATAN] ";
                  break;
                case KESALAHAN:
                  file << "[CATATAN][KESALAHAN] ";
                  break;
                default:
                  break;
              } // switch
              ((file << kumpulanPesan), ...);
              file << "\n";
              file.close();
            break;
        } // switch
      }  // function cetak

      template<typename... Types>
      static void cetakF(const TipeCatatan& tipe, const std::format_string<Types...>& formatString, const Types&... kumpulanPesan) {
        switch (tipe) {
          case INFO:
            nstd::cetak("\033[1;33m[CATATAN][INFO]\033[0m ");
            break;
          case PERINGATAN:
            nstd::cetak("\033[1;38;5;208m[CATATAN][PERINGATAN]\033[0m ");
            break;
          case KESALAHAN:
            nstd::cetak("\033[1;31m[CATATAN][KESALAHAN]\033[0m ");
            break;
          default:
            break;
        } // switch
        switch (tipe) {
          case INFO:
          case PERINGATAN:
          case KESALAHAN:
            nstd::cetakDBBDF(formatString, kumpulanPesan...);
              std::ofstream file(Catatan::ambilInstance()->lokasiBerkas, std::ios_base::app);
              switch (tipe) {
                case INFO:
                  file << "[CATATAN][INFO] ";
                  break;
                case PERINGATAN:
                  file << "[CATATAN][PERINGATAN] ";
                  break;
                case KESALAHAN:
                  file << "[CATATAN][KESALAHAN] ";
                  break;
                default:
                  break;
              } // switch
              file << std::vformat(formatString.get(), std::make_format_args(kumpulanPesan...)) << "\n";
              file.close();
            break;
        } // switch
      }  // function cetak
    // akhir dari access modifiers private
  
  }; // class Catatan

} // namespace nstd