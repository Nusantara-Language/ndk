/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_boolean_literal.h"
#include "nast/boolean_literal_nast.h"
#include "nparser.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseBooleanLiteral(NParser::Utils& utils)
{
    utils.expects({nlexer::NToken::Type::VALUE_TRUE_TOKEN, nlexer::NToken::Type::VALUE_FALSE_TOKEN}, "Bukanlah sebuah kata kunci logika.");

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

    return std::make_unique<BooleanLiteralNAst>(value);
}

} // namespace nparser