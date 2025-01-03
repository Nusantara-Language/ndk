/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef OP_RIGHTS_NAST_H
#define OP_RIGHTS_NAST_H

#include "nast/core/nast.h"
#include "nast/core/op_right.h"
#include <optional>
#include <utility>
#include <vector>

namespace nparser {

class OpRightsNAst
{
public:
    OpRightsNAst() = default;

    explicit OpRightsNAst(std::unique_ptr<NAst>&& left, std::vector<OpRight>&& opRights) : left(std::move(left)), opRights(std::move(opRights)) {}

    explicit OpRightsNAst(std::unique_ptr<NAst>&& left) : left(std::move(left)), opRights(std::nullopt) {}

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

}; // class OpRightsNAst

} // namespace nparser

#endif