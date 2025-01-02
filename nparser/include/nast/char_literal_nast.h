/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef CHAR_LITERAL_NAST_H
#define CHAR_LITERAL_NAST_H

#include "literal_nast.h"

namespace nparser {

class CharLiteralNAst : public LiteralNAst<char>
{
public:
    CharLiteralNAst() : LiteralNAst<char>('\0'){};
    explicit CharLiteralNAst(const char& value) : LiteralNAst<char>(value){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class CharLiteralNAst

} // namespace nparser

#endif