/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef TEKS_LITERAL_NAST_H
#define TEKS_LITERAL_NAST_H

#include "core/literal_nast.h"
#include "nast/core/nast.h"
#include <string>
#include <utility>

namespace nparser {

class TeksLiteralNAst : public NAst, public LiteralNAst<std::string>
{
public:
    TeksLiteralNAst() : LiteralNAst<std::string>("") {};
    explicit TeksLiteralNAst(std::string value) : LiteralNAst<std::string>(std::move(value)) {};
    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class TeksLiteralNAst

} // namespace nparser

#endif