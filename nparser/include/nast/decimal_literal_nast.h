/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef DECIMAL_LITERAL_NAST_H
#define DECIMAL_LITERAL_NAST_H

#include "literal_nast.h"

namespace nparser {

class DecimalLiteralNAst : public LiteralNAst<float>
{
public:
    DecimalLiteralNAst() : LiteralNAst<float>(0.0){};
    explicit DecimalLiteralNAst(const float& value) : LiteralNAst<float>(value){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class DecimalLiteralNAst

} // namespace nparser

#endif