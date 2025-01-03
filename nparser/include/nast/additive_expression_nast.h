/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef ADDITIVE_EXPRESSION_NAST_H
#define ADDITIVE_EXPRESSION_NAST_H

#include "core/op_rights_nast.h"
#include "nast/core/nast.h"
#include <vector>

namespace nparser {

class AdditiveExpressionNAst : public NAst, public OpRightsNAst
{
public:
    AdditiveExpressionNAst() = default;

    explicit AdditiveExpressionNAst(std::unique_ptr<NAst>&& left, std::vector<OpRight>&& opRights) : OpRightsNAst(std::move(left), std::move(opRights)) {}

    explicit AdditiveExpressionNAst(std::unique_ptr<NAst>&& left) : OpRightsNAst(std::move(left)) {}

    // akhir dari access modifiers public

}; // class AdditiveExpressionNAst

} // namespace nparser

#endif