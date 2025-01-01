/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PARSE_EXPRESSION_H
#define PARSE_EXPRESSION_H

#include "nparser.h"

namespace nparser {

std::unique_ptr<NAst> parseExpression(NParser::Utils& utils);

} // namespace nparser

#endif