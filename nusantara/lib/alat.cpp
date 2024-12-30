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

#include <format>
#include <fstream>
#include <stdexcept>

#include "alat.hpp"

std::filesystem::path nusantara::ambilLokasiBerkasProgram()
{
  static std::filesystem::path lokasiBerkasProgram;
  if (lokasiBerkasProgram.empty())
  {
#if defined(_WIN32)
    // Windows: Menggunakan GetModuleFileName
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    lokasiBerkasProgram = std::filesystem::absolute(buffer);
#elif defined(__linux__) || defined(__APPLE__)
    // Linux/MacOS: Menggunakan readlink untuk /proc/self/exe
    char buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
      buffer[len] = '\0';
      exePath = std::filesystem::absolute(buffer);
    }
#endif
  }
  return lokasiBerkasProgram;
}

std::string nusantara::bacaBerkasDalamBentukString(const std::string& lokasiBerkas)
{
  std::ifstream berkas(lokasiBerkas, std::ios::in | std::ios::binary);

  if (!berkas)
  {
    throw std::runtime_error(std::format("Gagal membaca berkas '{}'.", lokasiBerkas));
  }

  berkas.seekg(0, std::ios::end);
  std::size_t ukuranBerkas = berkas.tellg();
  berkas.seekg(0, std::ios::beg);

  std::string kontenBerkas(ukuranBerkas, '\0');

  berkas.read(&kontenBerkas[0], ukuranBerkas);

  return hapusRuangKosongDiAwalDanAkhirString(kontenBerkas);
}

std::vector<std::string> nusantara::pisahkanStringDenganPembatas(const std::string& str, const char& pembatas)
{
  std::vector<std::string> hasil;
  size_t awal = 0;
  size_t akhir = str.find(pembatas);

  while (akhir != std::string::npos)
  {
    hasil.push_back(str.substr(awal, akhir - awal));
    awal = akhir + 1;
    akhir = str.find(pembatas, awal);
  }
  hasil.push_back(str.substr(awal));

  return hasil;
}

std::string nusantara::hapusRuangKosongDiAwalDanAkhirString(const std::string& str)
{
  size_t start = 0;
  size_t end = str.size();

  while (start < end && std::isspace(static_cast<unsigned char>(str[start])))
  {
    ++start;
  }

  while (end > start && std::isspace(static_cast<unsigned char>(str[end - 1])))
  {
    --end;
  }

  return str.substr(start, end - start);
}

bool nusantara::apaKahStringNumeric(const std::string& str)
{
  if (str.empty())
    return false; // String kosong bukan nilaiBilangan
  for (char ch : str)
  {
    if (!std::isdigit(ch))
    {
      return false; // Jika ada karakter bukan digit
    }
  }
  return true; // Semua karakter adalah digit
}

std::string nusantara::hapusKanKutipDiAwalDanAkhirString(const std::string& str)
{
  return str.substr(1, str.size() - 2);
} // function hapusKanKutipDiAwalDanAkhirString