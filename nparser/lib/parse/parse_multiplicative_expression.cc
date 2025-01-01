/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_multiplicative_expression.h"
#include "nast/multiplicative_expression_nast.h"
#include "parse/parse_primary_expression.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseMultiplicativeExpression(NParser::Utils& utils)
{
    auto result = std::make_unique<MultiplicativeExpressionNAst>(parsePrimaryExpression(utils));

    while (utils.matchs({nlexer::NToken::Type::ASTERISK, nlexer::NToken::Type::SLASH, nlexer::NToken::Type::PERCENT}))
    {
        char op = utils.currentToken().content[0];
        utils.eat();
        result->addOpRight({op, parsePrimaryExpression(utils)});
    }

    return result;
}

} // namespace nparser