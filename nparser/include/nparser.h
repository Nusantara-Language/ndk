/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NPARSER_H
#define NPARSER_H

#include "nast/core/nast.h"
#include "nlexer.h"
#include "ntoken.h"
#include <error/file_content_exception.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

namespace nparser {

class NParser
{
public:
    struct Utils
    {
        Utils(std::reference_wrapper<nlexer::NToken::Wrapper> tWrap, std::reference_wrapper<NParser> parser) : tWrap(tWrap), parser(parser) {}

        std::reference_wrapper<nlexer::NToken::Wrapper> tWrap;
        std::reference_wrapper<NParser> parser;
        size_t index = 0;

        // Untuk memeriksa apakah token saat ini cocok dengan tipe yang diinginkan.
        [[nodiscard]] bool match(const nlexer::NToken::Type& type) const;

        // Untuk memeriksa apakah token saat ini cocok dengan beberapa tipe yang diinginkan.
        [[nodiscard]] bool matchs(const std::vector<nlexer::NToken::Type>& type) const;

        // Untuk melihat token berikut nya tanpa memajukan parser.
        [[nodiscard]] const nlexer::NToken& peek() const;

        // Untuk memajukan index parser
        void eat();

        // Untuk memastikan token yang di harapkan ada dan langsung memajukan index parser, digunakan ketika token yang diharapkan pasti ada
        void advance(const nlexer::NToken::Type& expectedType, const std::string& errorMessage);

        // Digunakan untuk memverifikasi dan memajukan index parser, jika tidak ada, maka akan melempar error
        void expect(const nlexer::NToken::Type& expectedType, const std::string& errorMessage);

        // Digunakan untuk memverifikasi dan memajukan index parser, jika tidak ada, maka akan melempar error
        void expects(const std::vector<nlexer::NToken::Type>& expectedTypes, const std::string& errorMessage);

        // Fungsi untuk membuat error yang menyertakan informasi
        [[nodiscard]] ncpp::FileContentException error(const std::string& errorMessage, const bool& prev = false) const;

        // Fungsi untuk melihat token beberapa langkah ke depan
        [[nodiscard]] const nlexer::NToken& lookhead(const size_t& offset) const;

        // Fungsi untuk melihat token saat ini
        [[nodiscard]] const nlexer::NToken& currentToken() const;

        // Fungsi untuk melihat token sebelumnya
        [[nodiscard]] const nlexer::NToken& prevToken() const;

        // fungsi untuk memajukan index parser hanya jika tipe token cocok
        void advanceIfMatch(const nlexer::NToken::Type& type);

        // fungsi untuk memeriksa apakah parser telah mencapai akhir dari file
        [[nodiscard]] bool isEndOfFile() const;

        // Fungsi untuk menghapus whitespace
        void skipWhiteSpace();
    };

    explicit NParser(const std::shared_ptr<nlexer::NLexer>& lexer, const std::shared_ptr<std::list<NAst::Wrapper>>& nAsts) : lexer(lexer), nAsts(nAsts) {}

    void input(const std::string& input, const std::string& path = "");
    void inputFile(const std::string& path);
    // akhir dari access modifiers public

private:
    std::shared_ptr<std::list<NAst::Wrapper>> nAsts;
    std::shared_ptr<nlexer::NLexer> lexer;
    std::unordered_set<std::string> fileLoaded;
    // akhir dari access modifiers private

protected:
    // akhir dari access modifiers protected

}; // class NParser

} // namespace nparser

#endif