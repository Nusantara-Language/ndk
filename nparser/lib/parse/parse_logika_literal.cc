/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_logika_literal.h"
#include "nast/logika_literal_nast.h"
#include "nparser.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseLogikaLiteral(NParser::Utils& utils)
{
    utils.expects({nlexer::NToken::Type::VALUE_BENAR_TOKEN, nlexer::NToken::Type::VALUE_SALAH_TOKEN}, "Bukanlah sebuah kata kunci logika.");

    bool value = false;
    if (utils.prevToken().content == "benar")
    {
        value = true;
    }
    else if (utils.prevToken().content == "salah")
    {
        value = false;
    }
    else
    {
        throw utils.error("Nilai logika tidak benar.", true);
    }

    return std::make_unique<LogikaLiteralNAst>(value);
}

} // namespace nparser