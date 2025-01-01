/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PARSE_STATEMENT_H
#define PARSE_STATEMENT_H

#include "nparser.h"

namespace nparser {

std::unique_ptr<NAst> parseStatement(NParser::Utils& utils);

} // namespace nparser

#endif