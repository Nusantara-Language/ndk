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
#include "parse/parse_unary_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseMultiplicativeExpression(NParser::Utils& utils)
{
    auto result = std::make_unique<MultiplicativeExpressionNAst>(parseUnaryExpression(utils));

    while (utils.matchs({nlexer::NToken::Type::ASTERISK_OP, nlexer::NToken::Type::SLASH_OP, nlexer::NToken::Type::PERCENT_OP}))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->addOpRight({op, parseUnaryExpression(utils)});
    }

    return result;
}

} // namespace nparser