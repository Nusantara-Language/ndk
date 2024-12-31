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

namespace nparser {

class NAst
{
public:
    NAst() = default;
    NAst(const NAst&) = delete;
    NAst(NAst&&) = default;
    NAst& operator=(const NAst&) = delete;
    NAst& operator=(NAst&&) = default;
    virtual ~NAst() = default;
    // akhir dari access modifiers public

private:

    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class AST

} // namespace nparser

#endif