/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_literal.h"
#include "nast/core/nast.h"
#include "nparser.h"
#include "parse/parse_logika_literal.h"
#include "parse/parse_karakter_literal.h"
#include "parse/parse_bilangan_desimal_literal.h"
#include "parse/parse_bilangan_bulat_literal.h"
#include "parse/parse_teks_literal.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseLiteral(NParser::Utils& utils)
{
    if (utils.match(nlexer::NToken::Type::BILANGAN_BULAT_LITERAL))
    {
        return parseBilanganBulatLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::BILANGAN_DESIMAL_LITERAL))
    {
        return parseBilanganDesimalLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::KARAKTER_LITERAL))
    {
        return parseKarakterLiteral(utils);
    }

    if (utils.match(nlexer::NToken::Type::TEKS_LITERAL))
    {
        return parseTeksLiteral(utils);
    }

    if (utils.matchs({nlexer::NToken::Type::VALUE_BENAR_TOKEN, nlexer::NToken::Type::VALUE_SALAH_TOKEN}))
    {
        return parseLogikaLiteral(utils);
    }

    throw utils.error("Bukan lah sebuah bilangan bulat, desimal, teks atau logika.");
}

} // namespace nparser