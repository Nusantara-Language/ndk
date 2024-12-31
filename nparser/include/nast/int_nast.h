/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef INT_NAST_H
#define INT_NAST_H

#include "nast.h"

namespace nparser {

class IntNAst : public NAst
{
public:
    inline explicit IntNAst(const int& value) : value(value) {}

    [[nodiscard]] int getValue() const
    {
        return value;
    }

    // akhir dari access modifiers public

private:
    int value;

    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class IntNAst

} // namespace nparser

#endif