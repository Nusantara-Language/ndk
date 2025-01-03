/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef LOGIKA_LITERAL_NAST_H
#define LOGIKA_LITERAL_NAST_H

#include "core/literal_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class LogikaLiteralNAst : public NAst, public LiteralNAst<bool>
{
public:
    LogikaLiteralNAst() : LiteralNAst<bool>(false) {};
    explicit LogikaLiteralNAst(const bool& value) : LiteralNAst<bool>(value) {};
    // akhir dari access modifiers public

}; // class LogikaLiteralNAst

} // namespace nparser

#endif