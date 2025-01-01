/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_literal.h"
#include "nast/literal_nast.h"
#include "nast/nast.h"
#include "nparser.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseLiteral(NParser::Utils& utils)
{
    utils.expects({nlexer::NToken::Type::INT, nlexer::NToken::Type::DECIMAL}, "Bukan lah sebuah bilangan bulat atau desimal.");
    return std::make_unique<LiteralNAst>(utils.prevToken());
}

} // namespace nparser