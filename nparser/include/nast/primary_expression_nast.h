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

#include "nast.h"
#include <memory>

namespace nparser {

class PrimaryExpressionNAst : public NAst
{
public:
    PrimaryExpressionNAst() = default;

    explicit PrimaryExpressionNAst(std::unique_ptr<NAst>&& value) : value(std::move(value)) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getValue() const
    {
        return value;
    }

    void setValue(std::unique_ptr<NAst>&& value)
    {
        this->value = std::move(value);
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> value = nullptr;
    // akhir dari access modifiers private

}; // class PrimaryExpressionNAst

} // namespace nparser

#endif