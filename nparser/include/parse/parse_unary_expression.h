/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PARSE_UNARY_EXPRESSION_H
#define PARSE_UNARY_EXPRESSION_H

#include "nast/core/nast.h"
#include "nparser.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseUnaryExpression(NParser::Utils& utils);

} // namespace nparser

#endif