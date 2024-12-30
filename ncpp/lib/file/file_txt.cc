/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "file/file_txt.h"
#include "string/string.h"
#include <format>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace ncpp {

FileTxt::FileTxt(std::string path) : File(std::move(path)) {}

std::string_view FileTxt::getContent()
{
    if (!this->ctnIsStr())
    {
        this->ctnToStr();
    }
    return this->gtCtnStr();
}

bool FileTxt::ctnIsStr()
{
    return std::holds_alternative<std::string>(this->gtEdtCtn());
}

void FileTxt::ctnToStr()
{
    auto& edtCtn = this->gtEdtCtn();
    if (this->ctnIsSpltStr())
    {
        edtCtn = join(std::get<std::vector<std::string>>(edtCtn), '\n');
    }
    else if (!this->ctnIsStr())
    {
        edtCtn = ncpp::normalized(ncpp::trimmed(ncpp::join(std::get<std::vector<char>>(edtCtn))));
    }
}

std::string_view FileTxt::gtCtnStr()
{
    return this->getEditableContent();
}

std::string& FileTxt::getEditableContent()
{
    if (!this->ctnIsStr())
    {
        this->ctnToStr();
    }
    return std::get<std::string>(this->gtEdtCtn());
}

const std::vector<std::string>& FileTxt::getContentWithLine()
{
    return this->gtEdtSpltCtnStr();
}

bool FileTxt::ctnIsSpltStr()
{
    return std::holds_alternative<std::vector<std::string>>(this->gtEdtCtn());
}

void FileTxt::spltCtnStr()
{
    if (!this->ctnIsStr())
    {
        this->ctnToStr();
    }
    if (!this->ctnIsSpltStr())
    {
        auto& edtCtn = this->gtEdtCtn();
        edtCtn = split(std::get<std::string>(edtCtn), '\n');
    }
}

std::vector<std::string>& FileTxt::gtEdtSpltCtnStr()
{
    if (!this->ctnIsSpltStr())
    {
        this->spltCtnStr();
    }
    return std::get<std::vector<std::string>>(this->gtEdtCtn());
}

std::string_view FileTxt::getContentInLine(const size_t& row)
{
    const auto& edtSpltCtnStr = this->gtEdtSpltCtnStr();
    const size_t& size = edtSpltCtnStr.size();
    if (row > (size - 1))
    {
        throw std::range_error(std::format("mencoba mengakses baris ke-{}, tapi di konten hanya ada {} baris", static_cast<int>(row) + 1, size));
    }
    return edtSpltCtnStr[row];
}

} // namespace ncpp