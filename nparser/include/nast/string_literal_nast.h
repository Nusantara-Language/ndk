/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef STRING_LITERAL_NAST_H
#define STRING_LITERAL_NAST_H

#include "literal_nast.h"
#include <string>
#include <utility>

namespace nparser {

class StringLiteralNAst : public LiteralNAst<std::string>
{
public:
    StringLiteralNAst() : LiteralNAst<std::string>(""){};
    explicit StringLiteralNAst(std::string value) : LiteralNAst<std::string>(std::move(value)){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class StringLiteralNAst

} // namespace nparser

#endif