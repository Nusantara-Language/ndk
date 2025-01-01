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

#include "nast/nast.h"
#include "ntoken.h"
#include <string>
#include <utility>

namespace nparser {

class LiteralNAst : public NAst
{
public:
    LiteralNAst() = default;

    explicit LiteralNAst(const nlexer::NToken& token) : value(token.content), location(token.location) {}

    explicit LiteralNAst(std::string value, const nlexer::NToken::Location& location) : value(std::move(value)), location(location) {}

    explicit LiteralNAst(std::string value) : value(std::move(value)) {}

    [[nodiscard]] const std::string& getValue() const
    {
        return value;
    }

    void setValue(const std::string& value)
    {
        this->value = value;
    }

    // akhir dari access modifiers public

private:
    std::string value;
    nlexer::NToken::Location location;
    // akhir dari access modifiers private

}; // class LiteralNAst

} // namespace nparser

#endif