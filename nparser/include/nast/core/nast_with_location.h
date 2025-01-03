/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NAST_WITH_LOCATION_H
#define NAST_WITH_LOCATION_H

#include "ntoken.h"

namespace nparser {

class NAstWithLocation
{
public:
    NAstWithLocation() = default;

    explicit NAstWithLocation(const nlexer::NToken::Location& location) : location(location) {}

    [[nodiscard]] const nlexer::NToken::Location& getLocation() const
    {
        return location;
    }

    // akhir dari access modifiers public

private:
    nlexer::NToken::Location location;
    // akhir dari access modifiers private

}; // class NAstWithLocation

} // namespace nparser

#endif