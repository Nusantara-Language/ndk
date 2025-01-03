/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_expression.h"
#include "nast/expression_nast.h"
#include "parse/parse_logical_or_expression.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseExpression(NParser::Utils& utils)
{
    return std::make_unique<ExpressionNAst>(parseLogicalOrExpression(utils));
}

} // namespace nparser