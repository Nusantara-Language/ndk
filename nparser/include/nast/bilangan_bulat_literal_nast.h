/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef BILANGAN_BULAT_LITERAL_NAST_H
#define BILANGAN_BULAT_LITERAL_NAST_H

#include "core/literal_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class BilanganBulatLiteralNAst : public NAst, public LiteralNAst<int>
{
public:
    BilanganBulatLiteralNAst() : LiteralNAst<int>(0){};
    explicit BilanganBulatLiteralNAst(const int& value) : LiteralNAst<int>(value){};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class BilanganBulatLiteralNAst

} // namespace nparser

#endif