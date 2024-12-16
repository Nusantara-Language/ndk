#pragma once

#include <regex>
#include <string>
#include <vector>

namespace Lexer
{

    enum TokenType 
    {
        TIDAK_DIKETAHUI,
        RUANG_KOSONG,
        BARIS_BARU,
        AKHIR_DARI_FILE,
        FUNGSI,
        IDENTIFIKASI,
        KURUNG_BULAT_BUKA,
        KURUNG_BULAT_TUTUP,
        KURUNG_KURAWAL_BUKA,
        KURUNG_KURAWAL_TUTUP,
    };

    struct Token 
    {
        std::string fileName;
        int row;
        int column;
        TokenType type;
        std::string content;
    };

    struct TokenRegex
    {
        std::regex regex;
        TokenType type;
    };

    std::string tokenTypeToString(TokenType const &type);
    void muatFile(std::string const &path, std::string &content);
    void createToken(std::string const &fileName, int const &row, int &column, std::smatch const &matches, TokenType const &TokenType, std::string &content, Token &token);
    void generateToken(std::string const &fileName, int &row, int &column, std::string &content, Token &token);
    void generateTokens(std::string const &fileName, int &row, int &column, std::string &content, std::vector<Token> &tokens);

}