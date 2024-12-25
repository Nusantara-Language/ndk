/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#if defined(_WIN32)
  #include <windows.h>
#elif defined(__linux__) || defined(__APPLE__)
  #include <unistd.h>
#endif

#include "alat.hpp"

std::filesystem::path nstd::ambilLokasiBerkasProgram() {
  static std::filesystem::path lokasiBerkasProgram;
  if(lokasiBerkasProgram.empty()) {
    #if defined(_WIN32)
      // Windows: Menggunakan GetModuleFileName
      char buffer[MAX_PATH];
      GetModuleFileName(NULL, buffer, MAX_PATH);
      lokasiBerkasProgram = std::filesystem::absolute(buffer);
    #elif defined(__linux__) || defined(__APPLE__)
      // Linux/MacOS: Menggunakan readlink untuk /proc/self/exe
      char buffer[1024];
      ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer)-1);
      if (len != -1) {
          buffer[len] = '\0';
          exePath = std::filesystem::absolute(buffer);
      }
    #endif
  }
  return lokasiBerkasProgram;
}