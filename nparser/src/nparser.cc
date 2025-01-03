/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nparser.h"
#include "nast/core/nast.h"
#include "nlexer.h"
#include "ntoken.h"
#include "utils/cout_nast.h"
#include <exception>
#include <iostream>
#include <memory>

int main(int argc, const char* argv[])
{
    try
    {
        auto tWraps = std::make_shared<std::list<nlexer::NToken::Wrapper>>();
        auto lexer = std::make_shared<nlexer::NLexer>(tWraps);
        auto aWraps = std::make_shared<std::list<nparser::NAst::Wrapper>>();
        nparser::NParser parser(lexer, aWraps);
        if (argc > 1)
        {
            for (int i = 1; i < argc; ++i)
            {
                parser.inputFile(argv[i]);
            }
        }
        for (const auto& aWrap : *aWraps)
        {
            std::cout << aWrap.Location << "\n";
            nparser::coutNAst(*aWrap.nAst);
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << "\n";
    }
    return 0;
}
