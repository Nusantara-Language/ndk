/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nparser.h"
#include "nast/nast.h"
#include "nast_addition.h"
#include "nlexer.h"
#include "ntoken.h"
#include <memory>
#include <vector>

int main(int argc, const char* argv[])
{
    auto tWraps = std::make_shared<std::vector<nlexer::NToken::Wrapper>>();
    auto lexer = std::make_shared<nlexer::NLexer>(tWraps);
    auto nAsts = std::make_shared<std::vector<std::unique_ptr<nparser::NAst>>>();
    nparser::NParser parser(lexer, nAsts);
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            parser.inputFile(argv[i]);
        }
    }
    for (const auto& nAst : *nAsts)
    {
        nparser::coutNAst(*nAst);
    }
    return 0;
}
