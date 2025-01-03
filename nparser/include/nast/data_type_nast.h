/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef DATA_TYPE_NAST_H
#define DATA_TYPE_NAST_H

#include "nast/core/nast.h"
#include "core/value_nast.h"
#include <string>


namespace nparser {

class DataTypeNAst : public NAst, public ValueNAst<std::string>
{
public:
    DataTypeNAst() = default;

    explicit DataTypeNAst(std::string value) : ValueNAst<std::string>(std::move(value)) {}

    // akhir dari access modifiers public

}; // class DataTypeNAst

} // namespace nparser

#endif