/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef STATEMENT_NAST_H
#define STATEMENT_NAST_H

#include "nast.h"

namespace nparser {

class StatementNAst : public NAst
{
public:
    StatementNAst() = default;

    explicit StatementNAst(std::unique_ptr<NAst>&& value) : value(std::move(value)) {}

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

}; // class StatementNAst

} // namespace nparser

#endif