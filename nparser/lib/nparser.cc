/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nparser.h"
#include "ntoken.h"
#include "parse/parse.h"
#include <algorithm>
#include <cctype>
#include <error/file_content_exception.h>
#include <filesystem>
#include <functional>
#include <memory>
#include <string>
#include <vector>

namespace nparser {

void NParser::input(const std::string& input, const std::string& path)
{
    // Menjadi path absolute dan dinormalisasi (menghapus simbol . dan ..)
    std::string pathAbsolute = std::filesystem::canonical(path).string();

    // Cek apakah path sudah dimuat sebelumnya
    if (this->fileLoaded.find(pathAbsolute) != this->fileLoaded.end())
    {
        // Jika sudah dimuat, akhiri fungsi
        return;
    }

    // Simpan path absolute yang sudah dinormalisasi ke dalam set
    this->fileLoaded.insert(pathAbsolute);

    // Lakukan pemrosesan file
    Utils utils{this->lexer->input(input, pathAbsolute), *this};
    this->nAsts->emplace_back(pathAbsolute, parse(utils));
}

void NParser::inputFile(const std::string& path)
{
    // Menjadi path absolute dan dinormalisasi (menghapus simbol . dan ..)
    std::string pathAbsolute = std::filesystem::canonical(path).string();

    // Cek apakah path sudah dimuat sebelumnya
    if (this->fileLoaded.find(pathAbsolute) != this->fileLoaded.end())
    {
        // Jika sudah dimuat, akhiri fungsi
        return;
    }

    // Simpan path absolute yang sudah dinormalisasi ke dalam set
    this->fileLoaded.insert(pathAbsolute);

    // Lakukan pemrosesan file
    Utils utils{this->lexer->inputFile(pathAbsolute), *this};
    this->nAsts->emplace_back(pathAbsolute, parse(utils));
}

// Untuk memeriksa apakah token saat ini cocok dengan tipe yang diinginkan.
bool NParser::Utils::match(const nlexer::NToken::Type& type) const
{
    return this->currentToken().type == type;
}

// Untuk memeriksa apakah token saat ini cocok dengan beberapa tipe yang diinginkan.
bool NParser::Utils::matchs(const std::vector<nlexer::NToken::Type>& type) const
{
    return std::any_of(type.begin(), type.end(),
        [this](const auto& type)
        {
            return this->match(type);
        });
}

// Untuk melihat token berikut nya tanpa memajukan parser.
[[nodiscard]] const nlexer::NToken& NParser::Utils::peek() const
{
    if (this->index + 1 < this->tWrap.get().tokens.size())
    {
        return this->tWrap.get().tokens[this->index + 1];
    }
    return this->tWrap.get().tokens[this->tWrap.get().tokens.size() - 1];
}

// Untuk memajukan index parser
void NParser::Utils::eat()
{
    if (this->index < this->tWrap.get().tokens.size() && currentToken().type != nlexer::NToken::NEOF_TOKEN)
    {
        ++this->index;
    }
}

// Untuk memastikan token yang di harapkan ada dan langsung memajukan index parser, digunakan ketika token yang diharapkan pasti ada
void NParser::Utils::advance(const nlexer::NToken::Type& expectedType, const std::string& errorMessage)
{
    if (match(expectedType))
    {
        eat();
    }
    else
    {
        throw error(errorMessage);
    }
}

// Digunakan untuk memverifikasi dan memajukan index parser, jika tidak ada, maka akan melempar error
void NParser::Utils::expect(const nlexer::NToken::Type& expectedType, const std::string& errorMessage)
{
    if (!match(expectedType))
    {
        throw error(errorMessage);
    }
    eat();
}

// Digunakan untuk memverifikasi dan memajukan index parser, jika tidak ada, maka akan melempar error
void NParser::Utils::expects(const std::vector<nlexer::NToken::Type>& expectedTypes, const std::string& errorMessage)
{
    if (!matchs(expectedTypes))
    {
        throw error(errorMessage);
    }
    eat();
}

// Fungsi untuk membuat error yang menyertakan informasi
[[nodiscard]] ncpp::FileContentException NParser::Utils::error(const std::string& errorMessage, const bool& prev) const
{
    return {ncpp::FileContentException::Type::ERROR, errorMessage, this->tWrap.get().location, prev ? this->prevToken().content : currentToken().content, prev ? this->prevToken().location.row : currentToken().location.row, prev ? this->prevToken().location.column : currentToken().location.column};
}

// Fungsi untuk melihat token beberapa langkah ke depan
[[nodiscard]] const nlexer::NToken& NParser::Utils::lookhead(const size_t& offset) const
{
    size_t lookaheadIndex = this->index + offset;
    if (lookaheadIndex < this->tWrap.get().tokens.size())
    {
        return this->tWrap.get().tokens[lookaheadIndex];
    }
    return this->tWrap.get().tokens[this->tWrap.get().tokens.size() - 1];
}

// Fungsi untuk melihat token saat ini
[[nodiscard]] const nlexer::NToken& NParser::Utils::currentToken() const
{
    return this->tWrap.get().tokens[this->index];
}

// Fungsi untuk melihat token sebelumnya
[[nodiscard]] const nlexer::NToken& NParser::Utils::prevToken() const
{
    return this->tWrap.get().tokens[std::max(0, static_cast<int>(this->index) - 1)];
}

// fungsi untuk memajukan index parser hanya jika tipe token cocok
void NParser::Utils::advanceIfMatch(const nlexer::NToken::Type& type)
{
    if (match(type))
    {
        eat();
    }
}

// fungsi untuk memeriksa apakah parser telah mencapai akhir dari file
[[nodiscard]] bool NParser::Utils::isEndOfFile() const
{
    return currentToken().type == nlexer::NToken::Type::NEOF_TOKEN;
}

// Fungsi untuk menghapus whitespace
void NParser::Utils::skipWhiteSpace()
{
    while (currentToken().type == nlexer::NToken::Type::WHITESPACE_TOKEN || currentToken().type == nlexer::NToken::Type::NEWLINE_TOKEN)
    {
        eat();
    }
}

} // namespace nparser
