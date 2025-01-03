/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef MULTIPLICATIVE_EXPRESSION_NAST_H
#define MULTIPLICATIVE_EXPRESSION_NAST_H

#include "core/op_right_nast.h"
#include "nast/core/nast.h"
#include <vector>

namespace nparser {

class MultiplicativeExpressionNAst : public NAst, public OpRightNAst
{
public:
    MultiplicativeExpressionNAst() = default;

    explicit MultiplicativeExpressionNAst(std::unique_ptr<NAst>&& left, std::vector<OpRight>&& opRights) : OpRightNAst(std::move(left), std::move(opRights)) {}

    explicit MultiplicativeExpressionNAst(std::unique_ptr<NAst>&& left) : OpRightNAst(std::move(left)) {}

    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class MultiplicativeExpressionNAst

} // namespace nparser

#endif