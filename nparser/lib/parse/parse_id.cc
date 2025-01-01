/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_id.h"
#include "nast/id_nast.h"
#include "nast/nast.h"
#include "nparser.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseId(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::ID, "Bukanlah sebuah identifikasi.");
    return std::make_unique<IdNAst>(utils.prevToken().content);
}

} // namespace nparser