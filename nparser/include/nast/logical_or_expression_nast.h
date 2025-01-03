/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef LOGICAL_OR_EXPRESSION_NAST_H
#define LOGICAL_OR_EXPRESSION_NAST_H

#include "core/op_right_nast.h"
#include "nast/core/nast.h"
#include <vector>

namespace nparser {

class LogicalOrExpressionNAst : public NAst, public OpRightNAst
{
public:
    LogicalOrExpressionNAst() = default;

    explicit LogicalOrExpressionNAst(std::unique_ptr<NAst>&& left, std::vector<OpRight>&& opRights) : OpRightNAst(std::move(left), std::move(opRights)) {}

    explicit LogicalOrExpressionNAst(std::unique_ptr<NAst>&& left) : OpRightNAst(std::move(left)) {}

    // akhir dari access modifiers public

}; // class LogicalOrExpressionNAst

} // namespace nparser

#endif