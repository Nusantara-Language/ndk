/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_teks_literal.h"
#include "nast/core/nast.h"
#include "nast/teks_literal_nast.h"
#include "nparser.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseTeksLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::TEKS_LITERAL, "Bukanlah sebuah teks.");

    std::string value = utils.prevToken().content;
    value = value.substr(1, value.size() - 2);

    return std::make_unique<TeksLiteralNAst>(value);
}

} // namespace nparser