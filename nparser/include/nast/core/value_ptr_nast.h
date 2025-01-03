/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef VALUE_PTR_NAST_H
#define VALUE_PTR_NAST_H

#include "nast/core/nast.h"
#include <memory>

namespace nparser {

class ValuePtrNAst
{
public:
    ValuePtrNAst() = default;

    explicit ValuePtrNAst(std::unique_ptr<NAst>&& value) : value(std::move(value)) {}

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

}; // class ValuePtrNAst

} // namespace nparser

#endif