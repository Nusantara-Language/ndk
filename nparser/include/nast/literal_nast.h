/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef LITERAL_NAST_H
#define LITERAL_NAST_H

#include "interface/ivalue.h"
#include "nast_with_location.h"
#include "ntoken.h"

namespace nparser {

template <typename Type>
class LiteralNAst : public ncpp::IValue<Type>, public NAstWithLocation
{
public:
    LiteralNAst() = default;

    explicit LiteralNAst(Type value) : ncpp::IValue<Type>(std::move(value)) {}

    explicit LiteralNAst(Type value, const nlexer::NToken::Location& location) : ncpp::IValue<Type>(std::move(value)), NAstWithLocation(location) {}

    // akhir dari access modifiers public

private:
    // akhir dari access modifiers private

}; // class LiteralNAst

} // namespace nparser

#endif