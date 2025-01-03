/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_relational_expression.h"
#include "nast/relational_expression_nast.h"
#include "parse/parse_additive_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseRelationalExpression(NParser::Utils& utils)
{
    std::unique_ptr<RelationalExpressionNAst> result = std::make_unique<RelationalExpressionNAst>(parseAdditiveExpression(utils));

    while (utils.matchs({
        nlexer::NToken::Type::LESS_THAN_OR_EQUAL_TO_OP,
        nlexer::NToken::Type::GREATER_THAN_OR_EQUAL_TO_OP,
        nlexer::NToken::Type::LESS_THAN_OP,
        nlexer::NToken::Type::GREATER_THAN_OP,
    }))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->addOpRight({op, parseAdditiveExpression(utils)});
    }

    return result;
}

} // namespace nparser