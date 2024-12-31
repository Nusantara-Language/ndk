/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "nlexer.h"
#include "ntoken.h"

int main(int argc, const char* argv[])
{
  std::shared_ptr<std::vector<nlexer::NToken::Wrapper>> tWraps = std::make_shared<std::vector<nlexer::NToken::Wrapper>>();
  nlexer::NLexer lexer(tWraps);
  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      lexer.inputFile(argv[i]);
    }
  }
  for (const auto& tWrap : *tWraps)
  {
    std::cout << tWrap;
  }
  return 0;
}