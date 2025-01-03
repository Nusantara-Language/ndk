/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef VALUE_LIST_PTR_NAST_H
#define VALUE_LIST_PTR_NAST_H

#include "nast/core/nast.h"
#include <list>

namespace nparser {

class ValueListPtrNAst
{
public:
    ValueListPtrNAst() = default;

    explicit ValueListPtrNAst(std::list<std::unique_ptr<NAst>>&& value) : value(std::move(value)) {}

    [[nodiscard]] const std::list<std::unique_ptr<NAst>>& getValue() const
    {
        return this->value;
    }

    void setValue(std::list<std::unique_ptr<NAst>>&& value)
    {
        this->value = std::move(value);
    }

    void addValue(std::unique_ptr<NAst>&& value)
    {
        this->value.emplace_back(std::move(value));
    }

    // akhir dari access modifiers public

private:
    std::list<std::unique_ptr<NAst>> value;

    // akhir dari access modifiers private

}; // class ValueListPtrNAst

} // namespace nparser

#endif