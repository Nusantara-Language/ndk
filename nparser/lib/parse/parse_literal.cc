/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_literal.h"
#include "nast/nast.h"
#include "nparser.h"
#include "parse/parse_decimal_literal.h"
#include "parse/parse_int_literal.h"
#include "parse/parse_string_literal.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseLiteral(NParser::Utils& utils)
{
    if (utils.match(nlexer::NToken::Type::INT))
    {
        return parseIntLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::DECIMAL))
    {
        return parseDecimalLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::STRING))
    {
        return parseStringLiteral(utils);
    }

    throw utils.error("Bukan lah sebuah bilangan bulat, desimal atau teks.");
}

} // namespace nparser