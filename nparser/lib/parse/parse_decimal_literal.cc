/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_decimal_literal.h"
#include "nast/decimal_literal_nast.h"
#include "nast/nast.h"
#include "nparser.h"
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseDecimalLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::DECIMAL_LITERAL, "Bukanlah sebuah bilangan desimal.");

    float value = 0.0;
    try
    {
        value = std::stof(utils.prevToken().content);
    }
    catch (const std::out_of_range& error)
    {
        throw utils.error("Bilangan desimal terlalu besar.", true);
    }
    catch (const std::exception& error)
    {
        throw utils.error(error.what(), true);
    }

    return std::make_unique<DecimalLiteralNAst>(value);
}

} // namespace nparser