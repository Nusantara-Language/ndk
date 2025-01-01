/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_int_literal.h"
#include "nast/int_literal_nast.h"
#include "nparser.h"
#include <exception>
#include <memory>
#include <stdexcept>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseIntLiteral(NParser::Utils& utils)
{
    utils.expect(nlexer::NToken::Type::INT, "Bukanlah sebuah bilangan bulat.");

    int value = 0;
    try
    {
        value = std::stoi(utils.prevToken().content);
    }
    catch (const std::out_of_range& error)
    {
        throw utils.error("Bilangan bulat terlalu besar.", true);
    }
    catch (const std::exception& error)
    {
        throw utils.error(error.what(), true);
    }

    return std::make_unique<IntLiteralNAst>(value);
}

} // namespace nparser