/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_data_type.h"
#include "nast/core/nast.h"
#include "nast/data_type_nast.h"
#include "ntoken.h"
#include <memory>

namespace nparser {

std::unique_ptr<nparser::NAst> parseDataType(NParser::Utils& utils)
{
    utils.expects({nlexer::NToken::Type::TYPE_BILANGAN_BULAT_TOKEN, nlexer::NToken::Type::TYPE_BILANGAN_DESIMAL_TOKEN, nlexer::NToken::Type::TYPE_KARAKTER_TOKEN, nlexer::NToken::Type::TYPE_TEKS_TOKEN, nlexer::NToken::Type::TYPE_LOGIKA_TOKEN}, "Bukanlah tipe data yang benar.");
    return std::make_unique<DataTypeNAst>(utils.prevToken().content);
}

} // namespace nparser