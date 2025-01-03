/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef UNARY_EXPRESSION_NAST_H
#define UNARY_EXPRESSION_NAST_H

#include "nast/core/nast.h"
#include "nast/core/value_ptr_nast.h"
#include <memory>
#include <optional>
#include <string>

namespace nparser {

class UnaryExpressionNAst : public NAst, public ValuePtrNAst
{
public:
    UnaryExpressionNAst() = default;

    UnaryExpressionNAst(std::optional<std::string>&& op, std::unique_ptr<NAst>&& value) : op(std::move(op)), ValuePtrNAst(std::move(value)) {}

    explicit UnaryExpressionNAst(std::unique_ptr<NAst>&& value) : ValuePtrNAst(std::move(value)) {}

    [[nodiscard]] const std::optional<std::string>& getOp() const
    {
        return this->op;
    }

    void setOp(std::optional<std::string>&& op)
    {
        this->op = op;
    }

    // akhir dari access modifiers public

private:
    std::optional<std::string> op = std::nullopt;
    // akhir dari access modifiers private

}; // class UnaryExpressionNAst

} // namespace nparser

#endif