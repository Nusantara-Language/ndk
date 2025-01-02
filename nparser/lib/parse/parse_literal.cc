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
#include "parse/parse_boolean_literal.h"
#include "parse/parse_char_literal.h"
#include "parse/parse_decimal_literal.h"
#include "parse/parse_int_literal.h"
#include "parse/parse_string_literal.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseLiteral(NParser::Utils& utils)
{
    if (utils.match(nlexer::NToken::Type::INT_LITERAL))
    {
        return parseIntLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::DECIMAL_LITERAL))
    {
        return parseDecimalLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::CHAR_LITERAL))
    {
        return parseCharLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::STRING_LITERAL))
    {
        return parseStringLiteral(utils);
    }

    if (utils.matchs({nlexer::NToken::Type::VALUE_TRUE_TOKEN, nlexer::NToken::Type::VALUE_FALSE_TOKEN}))
    {
        return parseBooleanLiteral(utils);
    }

    throw utils.error("Bukan lah sebuah bilangan bulat, desimal, teks atau logika.");
}

} // namespace nparser