/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef PRIMARY_EXPRESSION_NAST_H
#define PRIMARY_EXPRESSION_NAST_H

#include "core/value_ptr_nast.h"
#include "nast/core/nast.h"
#include <memory>

namespace nparser {

class PrimaryExpressionNAst : public NAst, public ValuePtrNAst
{
public:
    PrimaryExpressionNAst() = default;

    explicit PrimaryExpressionNAst(std::unique_ptr<NAst>&& value) : ValuePtrNAst(std::move(value)) {}

    // akhir dari access modifiers public

}; // class PrimaryExpressionNAst

} // namespace nparser

#endif