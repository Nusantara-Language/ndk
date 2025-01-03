/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_statement.h"
#include "nast/statement_nast.h"
#include "parse/parse_expression.h"
#include "parse/parse_variable.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseStatement(NParser::Utils& utils)
{
    std::unique_ptr<StatementNAst> statementNAst;

    if (utils.matchs({nlexer::NToken::Type::TYPE_BILANGAN_BULAT_TOKEN, nlexer::NToken::Type::TYPE_BILANGAN_DESIMAL_TOKEN, nlexer::NToken::Type::TYPE_KARAKTER_TOKEN, nlexer::NToken::Type::TYPE_TEKS_TOKEN, nlexer::NToken::Type::TYPE_LOGIKA_TOKEN}))
    {
        statementNAst = std::make_unique<StatementNAst>(parseVariable(utils));
    }
    else
    {
        statementNAst = std::make_unique<StatementNAst>(parseExpression(utils));
    }

    utils.expect(nlexer::NToken::SEMICOLON_TOKEN, "Jangan lupa titik koma.");

    return statementNAst;
}

} // namespace nparser