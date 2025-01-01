/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_compound_statement.h"
#include "nast/compound_statement_nast.h"
#include "parse/parse_statement.h"
#include <iostream>
#include <memory>

namespace nparser {

std::unique_ptr<NAst> parseCompoundStatement(NParser::Utils& utils)
{
    // Buat tempat untuk menampung kumpulan statement
    std::unique_ptr<CompoundStatementNAst> compoundStatements = std::make_unique<CompoundStatementNAst>();

    // Looping sampai akhir file
    while (!utils.isEndOfFile())
    {
        try
        {
            // Setiap iterasi panggil parse statement, dan masukkan hasil nya ke compoundStatement
            if (auto value = parseStatement(utils))
            {
                compoundStatements->addValue(std::move(value));
            }
        }
        catch (const std::exception& error)
        {
            std::cerr << error.what();
            utils.eat(); // Lanjutkan parsing meski ada error
        }
    }

    return compoundStatements;
}

} // namespace nparser