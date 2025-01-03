/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef OP_RIGHT_H
#define OP_RIGHT_H

#include "nast/core/nast.h"
#include <string>
#include <utility>

namespace nparser {

struct OpRight
{
    OpRight(std::string op, std::unique_ptr<NAst>&& right) : op(std::move(op)), right(std::move(right)) {}

    std::string op;
    std::unique_ptr<NAst> right;
};

} // namespace nparser

#endif