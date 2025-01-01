/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef COMPOUND_STATEMENT_NAST_H
#define COMPOUND_STATEMENT_NAST_H

#include "nast.h"
#include <vector>

namespace nparser {

class CompoundStatementNAst : public NAst
{
public:
    CompoundStatementNAst() = default;

    explicit CompoundStatementNAst(std::vector<std::unique_ptr<NAst>>&& value) : value(std::move(value)) {}

    [[nodiscard]] const std::vector<std::unique_ptr<NAst>>& getValue() const
    {
        return this->value;
    }

    void setValue(std::vector<std::unique_ptr<NAst>>&& value)
    {
        this->value = std::move(value);
    }

    void addValue(std::unique_ptr<NAst>&& value)
    {
        this->value.emplace_back(std::move(value));
    }

    // akhir dari access modifiers public

private:
    std::vector<std::unique_ptr<NAst>> value;

    // akhir dari access modifiers private

}; // class CompoundStatementNAst

} // namespace nparser

#endif