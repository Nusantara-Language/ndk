/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef KARAKTER_LITERAL_NAST_H
#define KARAKTER_LITERAL_NAST_H

#include "core/literal_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class KarakterLiteralNAst : public NAst, public LiteralNAst<char>
{
public:
    KarakterLiteralNAst() : LiteralNAst<char>('\0') {};
    explicit KarakterLiteralNAst(const char& value) : LiteralNAst<char>(value) {};
    // akhir dari access modifiers public

}; // class KarakterLiteralNAst

} // namespace nparser

#endif