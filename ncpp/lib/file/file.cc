/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include <filesystem>
#include <string>
#include <utility>
#include <variant>

#include "file/file.h"
#include "file/nnmap.h"

namespace ncpp {

File::File(std::string path) : pth(std::move(path)) {}

void File::read()
{
    this->ctn = nnmap(this->pth);
}

bool File::exist()
{
    return std::filesystem::exists(this->pth);
}

std::string_view File::getPath() noexcept
{
    return this->pth;
}

std::variant<std::vector<char>, std::string, std::vector<std::string>>& File::gtEdtCtn() noexcept
{
    return this->ctn;
}

} // namespace ncpp