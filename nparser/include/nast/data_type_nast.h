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

#include "interface/ivalue.h"
#include "nast/nast.h"
#include <string>

namespace nparser {

class DataTypeNAst : public ncpp::IValue<std::string>, public NAst
{
public:
    DataTypeNAst() = default;

    explicit DataTypeNAst(std::string value) : ncpp::IValue<std::string>(std::move(value)) {}

    // akhir dari access modifiers public

}; // class DataTypeNAst

} // namespace nparser

#endif