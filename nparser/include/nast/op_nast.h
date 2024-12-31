/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef OP_NAST_H
#define OP_NAST_H

#include "nast.h"
#include <memory>

namespace nparser {

class OpNAst : public NAst
{
public:
    inline explicit OpNAst(std::unique_ptr<NAst>&& left, const char& op, std::unique_ptr<NAst>&& right) : left(std::move(left)), op(op), right(std::move(right)) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getLeft() const
    {
        return left;
    }

    [[nodiscard]] const std::unique_ptr<NAst>& getRight() const
    {
        return right;
    }

    [[nodiscard]] const char& getOp() const
    {
        return op;
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> left;
    std::unique_ptr<NAst> right;
    char op;

    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class OpNAst

} // namespace nparser

#endif