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

#include "nast/core/nast.h"
#include "core/nast_with_location.h"
#include "core/value_nast.h"
#include "ntoken.h"
#include <string>

namespace nparser {

class IdNAst : public NAst, public ValueNAst<std::string>, public NAstWithLocation
{
public:
    IdNAst() = default;

    explicit IdNAst(std::string value) : ValueNAst<std::string>(std::move(value)) {}

    explicit IdNAst(std::string value, const nlexer::NToken::Location& location) : ValueNAst<std::string>(std::move(value)), NAstWithLocation(location) {}

    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class IdNAst

} // namespace nparser

#endif