/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_bilangan_desimal_literal.h"
#include "nast/bilangan_desimal_literal_nast.h"
#include "nast/core/nast.h"
#include "nparser.h"
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseBilanganDesimalLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::BILANGAN_DESIMAL_LITERAL, "Bukanlah sebuah bilangan desimal.");

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

    return std::make_unique<BilanganDesimalLiteralNAst>(value);
}

} // namespace nparser