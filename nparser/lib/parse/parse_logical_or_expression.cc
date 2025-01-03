/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_logical_or_expression.h"
#include "nast/logical_or_expression_nast.h"
#include "parse/parse_logical_and_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseLogicalOrExpression(NParser::Utils& utils)
{
    std::unique_ptr<LogicalOrExpressionNAst> result = std::make_unique<LogicalOrExpressionNAst>(parseLogicalAndExpression(utils));

    while (utils.match(nlexer::NToken::Type::LOGICAL_OR_OP))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->addOpRight({op, parseLogicalAndExpression(utils)});
    }

    return result;
}

} // namespace nparser