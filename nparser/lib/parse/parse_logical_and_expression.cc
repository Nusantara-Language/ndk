/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_logical_and_expression.h"
#include "nast/logical_and_expression_nast.h"
#include "parse/parse_additive_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseLogicalAndExpression(NParser::Utils& utils)
{
    std::unique_ptr<LogicalAndExpressionNAst> result = std::make_unique<LogicalAndExpressionNAst>(parseAdditiveExpression(utils));

    while (utils.match(nlexer::NToken::Type::LOGICAL_AND_OP))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->addOpRight({op, parseAdditiveExpression(utils)});
    }

    return result;
}

} // namespace nparser