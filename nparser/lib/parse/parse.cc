/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse.h"
#include "nast/compound_statement_nast.h"
#include "nast/core/nast.h"
#include "parse/parse_load_file.h"
#include "parse/parse_statement.h"
#include <iostream>

namespace nparser {

std::unique_ptr<nparser::NAst> parse(NParser::Utils& utils)
{
    // Gunakan alokasi stack untuk compound statements
    CompoundStatementNAst compoundStatements;

    bool isLoader = true;
    // Looping sampai akhir file
    while (!utils.isEndOfFile())
    {
        try
        {
            if (isLoader)
            {
                if (utils.match(nlexer::NToken::Type::LOAD_FILE_TOKEN))
                {
                    parseLoadFile(utils);
                    continue;
                }
                isLoader = false;
            }

            compoundStatements.addValue(parseStatement(utils));
        }
        catch (const std::exception& error)
        {
            std::cerr << error.what();
            utils.eat(); // Lanjutkan parsing meski ada error
        }
    }

    // Kembalikan hasil sebagai unique pointer
    return std::make_unique<CompoundStatementNAst>(std::move(compoundStatements));
}

} // namespace nparser