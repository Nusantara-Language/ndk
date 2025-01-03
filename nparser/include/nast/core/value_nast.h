/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef VALUE_NAST_H
#define VALUE_NAST_H

#include <algorithm>

namespace nparser {

template <typename Type>
class ValueNAst
{
public:
    ValueNAst() = default;

    explicit ValueNAst(Type value) : value(std::move(value)) {}

    [[nodiscard]] virtual const Type& getValue() const
    {
        return this->value;
    }

    virtual void setValue(Type value)
    {
        this->value = std::move(value);
    }

    // akhir dari access modifiers public

private:
    Type value;
    // akhir dari access modifiers private

}; // class ValueNAst

} // namespace ncpp

#endif