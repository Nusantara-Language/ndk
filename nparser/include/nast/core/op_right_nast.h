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
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace nparser {

struct OpRight
{
    OpRight(std::string op, std::unique_ptr<NAst>&& right) : op(std::move(op)), right(std::move(right)) {}

    std::string op;
    std::unique_ptr<NAst> right;
};

class OpRightNAst
{
public:
    OpRightNAst() = default;

    explicit OpRightNAst(std::unique_ptr<NAst>&& left, std::vector<OpRight>&& opRights) : left(std::move(left)), opRights(std::move(opRights)) {}

    explicit OpRightNAst(std::unique_ptr<NAst>&& left) : left(std::move(left)), opRights(std::nullopt) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getLeft() const
    {
        return this->left;
    }

    void setLeft(std::unique_ptr<NAst>&& left)
    {
        this->left = std::move(left);
    }

    [[nodiscard]] const std::optional<std::vector<OpRight>>& getOpRights() const
    {
        return this->opRights;
    }

    void setOpRights(std::vector<OpRight>&& opRights)
    {
        this->opRights = std::move(opRights);
    }

    void addOpRight(OpRight&& opRight)
    {
        if (!this->opRights.has_value())
        {
            this->opRights = std::vector<OpRight>();
        }
        this->opRights.value().emplace_back(std::move(opRight));
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> left;
    std::optional<std::vector<OpRight>> opRights;
    // akhir dari access modifiers private

}; // class OpRightNAst

} // namespace nparser

#endif