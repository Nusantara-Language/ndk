/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_additive_expression.h"
#include "nast/additive_expression_nast.h"
#include "parse/parse_multiplicative_expression.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseAdditiveExpression(NParser::Utils& utils)
{
    std::unique_ptr<AdditiveExpressionNAst> result = std::make_unique<AdditiveExpressionNAst>(parseMultiplicativeExpression(utils));

    while (utils.matchs({nlexer::NToken::Type::PLUS, nlexer::NToken::Type::MINUS}))
    {
        char op = utils.currentToken().content[0];
        utils.eat();
        result->addOpRight({op, parseMultiplicativeExpression(utils)});
    }

    return result;
}

} // namespace nparser