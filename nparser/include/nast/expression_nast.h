/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef EXPRESSION_NAST_H
#define EXPRESSION_NAST_H

#include "nast/core/nast.h"
#include "core/value_ptr_nast.h"

namespace nparser {

class ExpressionNAst : public NAst, public ValuePtrNAst
{
public:
    ExpressionNAst() = default;

    explicit ExpressionNAst(std::unique_ptr<NAst>&& value) : ValuePtrNAst(std::move(value)) {}

    // akhir dari access modifiers public

}; // class ExpressionNAst

} // namespace nparser

#endif