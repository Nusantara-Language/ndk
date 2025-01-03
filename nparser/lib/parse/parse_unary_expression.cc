/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_unary_expression.h"
#include "nast/unary_expression_nast.h"
#include "parse/parse_primary_expression.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseUnaryExpression(NParser::Utils& utils)
{
    auto result = std::make_unique<UnaryExpressionNAst>();

    if (utils.match(nlexer::NToken::Type::LOGICAL_NOT_OP))
    {
        utils.eat();
        result->setOp(utils.prevToken().content);
    }

    result->setValue(parsePrimaryExpression(utils));

    return result;
}

} // namespace nparser