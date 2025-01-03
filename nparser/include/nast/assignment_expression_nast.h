/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef ASSIGNMENT_EXPRESSION_NAST_H
#define ASSIGNMENT_EXPRESSION_NAST_H

#include "core/op_right_nast.h"
#include "nast/core/nast.h"

namespace nparser {

class AssignmentExpressionNAst : public NAst, public OpRightNAst
{
public:
    AssignmentExpressionNAst() = default;

    explicit AssignmentExpressionNAst(std::unique_ptr<NAst>&& left, OpRight&& opRight) : OpRightNAst(std::move(left), std::move(opRight)) {}

    explicit AssignmentExpressionNAst(std::unique_ptr<NAst>&& left) : OpRightNAst(std::move(left)) {}

    // akhir dari access modifiers public

}; // class AssignmentExpressionNAst

} // namespace nparser

#endif