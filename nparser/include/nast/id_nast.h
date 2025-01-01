/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef ID_NAST_H
#define ID_NAST_H

#include "interface/ivalue.h"
#include "nast_with_location.h"
#include "ntoken.h"
#include <string>

namespace nparser {

class IdNAst : public ncpp::IValue<std::string>, public NAstWithLocation
{
public:
    IdNAst() = default;

    explicit IdNAst(std::string value) : ncpp::IValue<std::string>(std::move(value)) {}

    explicit IdNAst(std::string value, const nlexer::NToken::Location& location) : ncpp::IValue<std::string>(std::move(value)), NAstWithLocation(location) {}

    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class IdNAst

} // namespace nparser

#endif