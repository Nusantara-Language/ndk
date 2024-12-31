/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#include "nparser.h"
#include "nast/compound_statement_nast.h"
#include "nast/expression_nast.h"
#include "nast/int_nast.h"
#include "nast/nast.h"
#include "nast/op_nast.h"
#include "nast/statement_nast.h"
#include "ntoken.h"
#include <algorithm>
#include <cctype>
#include <error/file_content_exception.h>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace nparser {

std::unique_ptr<nparser::NAst>& NParser::input(const std::string& input, const std::string& path)
{
    Utils utils{this->lexer->input(input, path), *this->lexer, *this};
    this->nAsts->emplace_back(std::move(parse(utils)));
    return this->nAsts->back();
}

std::unique_ptr<nparser::NAst>& NParser::inputFile(const std::string& path)
{
    Utils utils{this->lexer->inputFile(path), *this->lexer, *this};
    this->nAsts->emplace_back(std::move(parse(utils)));
    return this->nAsts->back();
}

std::unique_ptr<nparser::NAst> NParser::parse(Utils& utils)
{
    // Langsung parse ke kumpulan statement.
    return parseCompoundStatement(utils);
}

std::unique_ptr<nparser::NAst> NParser::parseCompoundStatement(Utils& utils)
{
    // Buat tempat untuk menampung kumpulan statement
    std::vector<std::unique_ptr<nparser::NAst>> compoundStatementValue;

    // Looping sampai akhir file
    while (!utils.isEndOfFile())
    {
        try
        {
            // Setiap iterasi panggil parse statement, dan masukkan hasil nya ke compoundStatement
            compoundStatementValue.emplace_back(parseStatement(utils));
        }
        catch (const std::exception& error)
        {
            std::cerr << error.what();
            utils.eat(); // Lanjutkan parsing meski ada error
        }
    }

    return std::make_unique<CompoundStatementNAst>(std::move(compoundStatementValue));
}

std::unique_ptr<nparser::NAst> NParser::parseStatement(Utils& utils)
{
    std::unique_ptr<NAst> nAst;

    // Cek apakah statment berisi int, jika iya statement adalah ekspresi
    if (utils.match(nlexer::NToken::Type::INT))
    {
        // Mengatur statemnt menjadi ekspresi.
        nAst = parseExpression(utils);
    }
    else
    {
        // Lempar error jika token saat ini bukan sebuah int.
        throw utils.error("Saat ini statement yang tersedia hanyalah bilangan.");
    }

    // Pastikan ada titik koma setelah statement
    utils.expect(nlexer::NToken::SEMICOLON, "Jangan lupa titik koma.");

    return std::make_unique<StatementNAst>(std::move(nAst));
}

std::unique_ptr<nparser::NAst> NParser::parseExpression(Utils& utils)
{
    std::unique_ptr<NAst> nAst;

    // Cek apakah statement berisi int
    if (utils.match(nlexer::NToken::Type::INT))
    {
        // Mengatur ekspresi menjadi operasi
        nAst = parseOp(utils);
    }
    else
    {
        // Lempar error jika token saat ini bukan sebuah int.
        throw utils.error("Saat ini statement yang tersedia hanyalah bilangan.");
    }

    return std::make_unique<ExpressionNAst>(std::move(nAst));
}

std::unique_ptr<nparser::NAst> NParser::parseOp(Utils& utils)
{
    // Buat variabel untuk data di sebelah kiri, dari parseInt
    std::unique_ptr<NAst> left = parseInt(utils);

    // Looping jika token selanjutnya ada operator, lakukan operasi sesuai token
    while (utils.matchs({nlexer::NToken::Type::PLUS, nlexer::NToken::Type::MINUS, nlexer::NToken::Type::ASTERISK, nlexer::NToken::Type::SLASH, nlexer::NToken::Type::PERCENT}))
    {
        // Simpan simbol operasi
        char op = utils.currentToken().content[0];

        // Maju ke token selanjutnya
        utils.eat();

        // Lempar error jika token selanjutnya bukan bilangan
        if (!utils.match(nlexer::NToken::Type::INT))
        {
            throw utils.error("Ini bukanlah sebuah bilangan.");
        }

        // Buat variabel untuk data di sebelah kanan, dari parseInt
        std::unique_ptr<NAst> right = parseInt(utils);

        // Gabungkan kiri dan kanan dengan operator
        left = std::make_unique<OpNAst>(std::move(left), op, std::move(right));
    }

    return left;
}

std::unique_ptr<nparser::NAst> NParser::parseInt(Utils& utils)
{
    // Pastikan token saat ini adalah INT
    utils.expect(nlexer::NToken::INT, "Bukanlah sebuah bilangan bulat.");
    int value = 0;
    try
    {
        value = std::stoi(utils.prevToken().content);
    }
    catch (const std::out_of_range& error)
    {
        throw utils.error("Bilangan bulat terlalu besar", true);
    }
    catch (const std::exception& error)
    {
        throw utils.error(error.what(), true);
    }
    return std::make_unique<IntNAst>(value);
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
    if (this->index < this->tWrap.get().tokens.size() && currentToken().type != nlexer::NToken::NEOF)
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
    return currentToken().type == nlexer::NToken::Type::NEOF;
}

// Fungsi untuk menghapus whitespace
void NParser::Utils::skipWhiteSpace()
{
    while (currentToken().type == nlexer::NToken::Type::WHITESPACE || currentToken().type == nlexer::NToken::Type::NEWLINE)
    {
        eat();
    }
}

} // namespace nparser
