/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef INT_LITERAL_NAST_H
#define INT_LITERAL_NAST_H

#include "literal_nast.h"

namespace nparser {

class IntLiteralNAst : public LiteralNAst<int>
{
public:
    IntLiteralNAst() : LiteralNAst<int>(0){};
    explicit IntLiteralNAst(const int& value) : LiteralNAst<int>(value){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class IntLiteralNAst

} // namespace nparser

#endif