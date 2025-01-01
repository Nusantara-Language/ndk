/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef COUT_NAST_H
#define COUT_NAST_H

#include "nast/nast.h"

namespace nparser {

void coutNAst(const NAst& nAst, int indent = 0);

} // namespace nparser

#endif