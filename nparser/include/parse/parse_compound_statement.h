/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PARSE_COMPOUND_STATEMENT_H
#define PARSE_COMPOUND_STATEMENT_H

#include "nast/nast.h"
#include "nparser.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseCompoundStatement(NParser::Utils& utils);

} // namespace nparser

#endif