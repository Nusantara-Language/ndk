/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_char_literal.h"
#include "nast/char_literal_nast.h"
#include "nast/nast.h"
#include "nparser.h"
#include <memory>
#include <string>


namespace nparser {

std::unique_ptr<NAst> parseCharLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::CHAR_LITERAL, "Bukanlah sebuah karakter.");
    char value = utils.prevToken().content[1];
    return std::make_unique<CharLiteralNAst>(value);
}

} // namespace nparser