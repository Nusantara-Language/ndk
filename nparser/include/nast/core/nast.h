/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NAST_H
#define NAST_H

#include <memory>
#include <string>

namespace nparser {

class NAst
{
public:
    struct Wrapper
    {
        std::string Location;       ///< Lokasi input atau file sumber.
        std::unique_ptr<NAst> nAst; ///< NAst yang di hasilkan dari parsing file sumber.
    };

    NAst() = default;
    NAst(const NAst&) = delete;
    NAst(NAst&&) = default;
    NAst& operator=(const NAst&) = delete;
    NAst& operator=(NAst&&) = default;
    virtual ~NAst() = default;
    // akhir dari access modifiers public

}; // class NAst

} // namespace nparser

#endif