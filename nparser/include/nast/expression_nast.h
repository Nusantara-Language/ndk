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

#include "nast.h"

namespace nparser {

class ExpressionNAst : public NAst
{
public:
    ExpressionNAst() = default;

    explicit ExpressionNAst(std::unique_ptr<NAst>&& value) : value(std::move(value)) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getValue() const
    {
        return this->value;
    }

    void setValue(std::unique_ptr<NAst>&& value)
    {
        this->value = std::move(value);
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> value;

    // akhir dari access modifiers private

}; // class ExpressionNAst

} // namespace nparser

#endif