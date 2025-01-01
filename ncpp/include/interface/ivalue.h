/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef IVALUE_H
#define IVALUE_H

#include <algorithm>

namespace ncpp {

template <typename Type>
class IValue
{
public:
    IValue() = default;

    explicit IValue(Type value) : value(std::move(value)) {}

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

}; // class IValue

} // namespace ncpp

#endif