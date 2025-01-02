/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef VARIABLE_NAST_H
#define VARIABLE_NAST_H

#include "nast/nast.h"
#include <memory>
#include <optional>
#include <string>
#include <utility>

namespace nparser {

class VariableNAst : public NAst
{
public:
    VariableNAst() = default;

    VariableNAst(std::unique_ptr<NAst>&& dataType, std::string name) : dataType(std::move(dataType)), name(std::move(name)), init(std::nullopt) {}

    VariableNAst(std::unique_ptr<NAst>&& dataType, std::string name, std::optional<std::unique_ptr<NAst>>&& init) : dataType(std::move(dataType)), name(std::move(name)), init(std::move(init)) {}

    [[nodiscard]] const std::unique_ptr<NAst>& getDataType() const
    {
        return this->dataType;
    }

    void setDataType(std::unique_ptr<NAst>&& dataType)
    {
        this->dataType = std::move(dataType);
    }

    [[nodiscard]] const std::string& getName() const
    {
        return this->name;
    }

    void setName(std::string name)
    {
        this->name = std::move(name);
    }

    [[nodiscard]] const std::optional<std::unique_ptr<NAst>>& getInit() const
    {
        return this->init;
    }

    void setInit(std::optional<std::unique_ptr<NAst>>&& init)
    {
        this->init = std::move(init);
    }

    // akhir dari access modifiers public

private:
    std::unique_ptr<NAst> dataType;
    std::string name;
    std::optional<std::unique_ptr<NAst>> init;
    // akhir dari access modifiers private

}; // class VariableNAst

} // namespace nparser

#endif