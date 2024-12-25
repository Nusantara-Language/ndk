/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#pragma once

#include <set>

#include "token/token_regex.hpp"

namespace nusantara {

  auto nusantaraTokenRegexs() -> const std::set<TokenRegex>&;

} // namespace nusantara