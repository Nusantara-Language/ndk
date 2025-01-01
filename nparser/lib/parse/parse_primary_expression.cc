/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_primary_expression.h"
#include "nast/primary_expression_nast.h"
#include "nparser.h"
#include "parse/parse_expression.h"
#include "parse/parse_id.h"
#include "parse/parse_literal.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parsePrimaryExpression(NParser::Utils& utils)
{
    auto primaryExpressionNAst = std::make_unique<PrimaryExpressionNAst>();
    if (utils.match(nlexer::NToken::Type::OPEN_ROUND_BRACKET))
    {
        utils.eat();
        primaryExpressionNAst->setValue(parseExpression(utils));
        utils.expect(nlexer::NToken::Type::CLOSE_ROUND_BRACKET, "Kurung bulat buka tidak memiliki penutup.");
    }
    else if (utils.match(nlexer::NToken::Type::ID))
    {
        primaryExpressionNAst->setValue(parseId(utils));
    }
    else
    {
        primaryExpressionNAst->setValue(parseLiteral(utils));
    }
    return primaryExpressionNAst;
}

} // namespace nparser