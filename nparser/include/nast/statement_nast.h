/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef STATEMENT_NAST_H
#define STATEMENT_NAST_H

#include "core/value_ptr_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class StatementNAst : public NAst, public ValuePtrNAst
{
public:
    StatementNAst() = default;

    explicit StatementNAst(std::unique_ptr<NAst>&& value) : ValuePtrNAst(std::move(value)) {}

    // akhir dari access modifiers public

}; // class StatementNAst

} // namespace nparser

#endif