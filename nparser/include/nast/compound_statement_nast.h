/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef COMPOUND_STATEMENT_NAST_H
#define COMPOUND_STATEMENT_NAST_H

#include "nast/core/nast.h"
#include "core/value_list_ptr_nast.h"
#include <list>

namespace nparser {

class CompoundStatementNAst : public NAst, public ValueListPtrNAst
{
public:
    CompoundStatementNAst() = default;

    explicit CompoundStatementNAst(std::list<std::unique_ptr<NAst>>&& value) : ValueListPtrNAst(std::move(value)) {}

    // akhir dari access modifiers public

}; // class CompoundStatementNAst

} // namespace nparser

#endif