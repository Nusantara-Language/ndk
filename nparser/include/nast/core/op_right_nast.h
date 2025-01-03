/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef OP_RIGHT_NAST_H
#define OP_RIGHT_NAST_H

#include "nast/core/nast.h"
#include "nast/core/op_right.h"
#include <optional>
#include <utility>

namespace nparser {

class OpRightNAst
{
public:
    OpRightNAst() = default;

    explicit OpRightNAst(std::unique_ptr<NAst>&& left, OpRight&& opRight) : left(std::move(left)), opRight(std::move(opRight)) {}

    explicit OpRightNAst(std::unique_ptr<NAst>&& left) : left(std::move(left)), opRight(std::nullopt) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getLeft() const
    {
        return this->left;
    }

    void setLeft(std::unique_ptr<NAst>&& left)
    {
        this->left = std::move(left);
    }

    [[nodiscard]] const std::optional<OpRight>& getOpRight() const
    {
        return this->opRight;
    }

    void setOpRight(OpRight&& opRight)
    {
        this->opRight = std::move(opRight);
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> left;
    std::optional<OpRight> opRight;
    // akhir dari access modifiers private

}; // class OpRightNAst

} // namespace nparser

#endif