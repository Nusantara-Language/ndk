/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_karakter_literal.h"
#include "nast/core/nast.h"
#include "nast/karakter_literal_nast.h"
#include "nparser.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseKarakterLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::KARAKTER_LITERAL, "Bukanlah sebuah karakter.");
    char value = utils.prevToken().content[1];
    return std::make_unique<KarakterLiteralNAst>(value);
}

} // namespace nparser