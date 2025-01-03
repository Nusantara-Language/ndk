/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef BILANGAN_DESIMAL_LITERAL_NAST_H
#define BILANGAN_DESIMAL_LITERAL_NAST_H

#include "core/literal_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class BilanganDesimalLiteralNAst : public NAst, public LiteralNAst<float>
{
public:
    BilanganDesimalLiteralNAst() : LiteralNAst<float>(0.0) {};
    explicit BilanganDesimalLiteralNAst(const float& value) : LiteralNAst<float>(value) {};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class BilanganDesimalLiteralNAst

} // namespace nparser

#endif