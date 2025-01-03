/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_assignment_expression.h"
#include "nast/assignment_expression_nast.h"
#include "parse/parse_logical_or_expression.h"
#include <memory>
#include <string>

namespace nparser {

std::unique_ptr<NAst> parseAssignmentExpression(NParser::Utils& utils)
{
    std::unique_ptr<AssignmentExpressionNAst> result = std::make_unique<AssignmentExpressionNAst>(parseLogicalOrExpression(utils));

    if (utils.matchs({
            nlexer::NToken::Type::ASSIGNMENT_OP,
            nlexer::NToken::Type::ADDITION_ASSIGN_OP,
            nlexer::NToken::Type::SUBTRACTION_ASSIGN_OP,
            nlexer::NToken::Type::MULTIPLICATION_ASSIGN_OP,
            nlexer::NToken::Type::DIVISION_ASSIGN_OP,
            nlexer::NToken::Type::MODULO_ASSIGN_OP,
            nlexer::NToken::Type::BITWISE_LEFT_SHIFT_ASSIGN_OP,
            nlexer::NToken::Type::BITWISE_RIGHT_SHIFT_ASSIGN_OP,
            nlexer::NToken::Type::BITWISE_AND_ASSIGN_OP,
            nlexer::NToken::Type::BITWISE_OR_ASSIGN_OP,
            nlexer::NToken::Type::BITWISE_XOR_ASSIGN_OP,
        }))
    {
        std::string op = utils.currentToken().content;
        utils.eat();
        result->setOpRight({op, parseLogicalOrExpression(utils)});
    }

    return result;
}

} // namespace nparser