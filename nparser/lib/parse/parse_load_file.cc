/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "parse/parse_load_file.h"
#include "ntoken.h"
#include <exception>
#include <string>

namespace nparser {

void parseLoadFile(NParser::Utils& utils) {
    utils.expect(nlexer::NToken::Type::LOAD_FILE_KEYWORD, "Bukanlah kata kunci untuk memuat berkas.");

    utils.expect(nlexer::NToken::Type::STRING, "Bukanlah lokasi berkas yang benar.");

    std::string path = utils.prevToken().content;
    path = path.substr(1, path.size() - 2);

    try {
        utils.parser.get().inputFile(path);
    }catch(const std::exception& error) {
        throw utils.error("Tidak dapat menemukan berkas ini.", true);
    }
}

} // namespace nparser