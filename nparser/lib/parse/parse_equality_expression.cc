/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_equality_expression.h"
#include "nast/equality_expression_nast.h"
#include "parse/parse_relational_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseEqualityExpression(NParser::Utils& utils)
{
    std::unique_ptr<EqualityExpressionNAst> result = std::make_unique<EqualityExpressionNAst>(parseRelationalExpression(utils));

    while (utils.matchs({
        nlexer::NToken::Type::EQUAL_TO_OP,
        nlexer::NToken::Type::NOT_EQUAL_OP,
    }))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->addOpRight({op, parseRelationalExpression(utils)});
    }

    return result;
}

} // namespace nparser