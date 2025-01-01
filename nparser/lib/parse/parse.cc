/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse.h"
#include "nast/nast.h"
#include "parse/parse_compound_statement.h"

namespace nparser {

std::unique_ptr<nparser::NAst> parse(NParser::Utils& utils)
{
    // Langsung parse ke kumpulan statement.
    return parseCompoundStatement(utils);
}

} // namespace nparser