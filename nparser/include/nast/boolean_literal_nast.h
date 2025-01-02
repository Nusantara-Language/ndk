/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef BOOLEAN_LITERAL_NAST_H
#define BOOLEAN_LITERAL_NAST_H

#include "literal_nast.h"

namespace nparser {

class BooleanLiteralNAst : public LiteralNAst<bool>
{
public:
    BooleanLiteralNAst() : LiteralNAst<bool>(false){};
    explicit BooleanLiteralNAst(const bool& value) : LiteralNAst<bool>(value){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class BooleanLiteralNAst

} // namespace nparser

#endif