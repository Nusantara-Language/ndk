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
#include "parse/parse_load_file.h"
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseStatement(NParser::Utils& utils)
{
    std::unique_ptr<StatementNAst> statementNAst = nullptr;

    if(utils.match(nlexer::NToken::Type::LOAD_FILE_KEYWORD)) {
        parseLoadFile(utils);
    }else{
        statementNAst = std::make_unique<StatementNAst>(parseExpression(utils));
    }

    utils.expect(nlexer::NToken::SEMICOLON, "Jangan lupa titik koma.");

    return statementNAst;
}

} // namespace nparser