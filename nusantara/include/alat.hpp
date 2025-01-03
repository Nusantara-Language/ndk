/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef ALAT_HPP
#define ALAT_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace nusantara {

std::filesystem::path ambilLokasiBerkasProgram();

std::string bacaBerkasDalamBentukString(const std::string& lokasiBerkas);

std::vector<std::string> pisahkanStringDenganPembatas(const std::string& str, const char& pembatas);

std::string hapusRuangKosongDiAwalDanAkhirString(const std::string& str);

bool apaKahStringNumeric(const std::string& str);

std::string hapusKanKutipDiAwalDanAkhirString(const std::string& str);

} // namespace nusantara

#endif
