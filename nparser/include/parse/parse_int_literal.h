/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PARSE_INT_LITERAL_H
#define PARSE_INT_LITERAL_H

#include "nast/nast.h"
#include "nparser.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseIntLiteral(NParser::Utils& utils);

} // namespace nparser

#endif