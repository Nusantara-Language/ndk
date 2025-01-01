/*
 * ----------------------------------------------------------------------------
 * Proyek: Nusantara Language
 * Penulis: Fern Aerell
 * Lisensi: BSD 3-Clause License
 * Hak Cipta (c) 2024, Nusantara
 * ----------------------------------------------------------------------------
 */

#ifndef NTOKEN_H
#define NTOKEN_H

#include <array>
#include <cstddef>
#include <cstdio>
#include <ostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

namespace nlexer {

/**
 * @brief Struktur yang merepresentasikan token dalam lexer.
 */
struct NToken
{
    /**
     * @brief Struktur yang membungkus daftar token dan lokasi sumber.
     */
    struct Wrapper
    {
        std::string location;       ///< Lokasi input atau file sumber
        std::vector<NToken> tokens; ///< Daftar token yang dihasilkan

        /**
         * @brief Operator untuk mencetak Wrapper ke output stream.
         * @param os Output stream yang digunakan untuk mencetak.
         * @param wrp Wrapper yang akan dicetak.
         * @return Referensi ke output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Wrapper& wrp)
        {
            for (const auto& token : wrp.tokens)
            {
                os << wrp.location << ":" << token << "\n";
            }
            return os;
        } // operator<<
    }; // struct Wrapper

    /**
     * @brief Struktur yang merepresentasikan lokasi token dalam file.
     */
    struct Location
    {
        size_t row = 0;    ///< Nomor baris dari lokasi token
        size_t column = 0; ///< Nomor kolom dari lokasi token

        /**
         * @brief Operator untuk mencetak Location ke output stream.
         * @param os Output stream yang digunakan untuk mencetak.
         * @param location Lokasi yang akan dicetak.
         * @return Referensi ke output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Location& location)
        {
            os << location.row << ":" << location.column;
            return os;
        } // operator<<
    }; // struct Location

    /**
     * @brief Enum yang mendefinisikan jenis-jenis token.
     */

    // TOKEN_TYPE_TARGET
enum Type {
  NEWLINE = 0,
  WHITESPACE = 1,
  SINGLE_LINE_COMMENT = 2,
  MULTI_LINE_COMMENT = 3,
  LOAD_FILE_KEYWORD = 4,
  INT_KEYWORD = 5,
  DECIMAL_KEYWORD = 6,
  STRING_KEYWORD = 7,
  CHAR_KEYWORD = 8,
  BOOLEAN_KEYWORD = 9,
  TRUE_KEYWORD = 10,
  FALSE_KEYWORD = 11,
  OPEN_CURLY_BRACKET = 12,
  CLOSE_CURLY_BRACKET = 13,
  OPEN_ROUND_BRACKET = 14,
  CLOSE_ROUND_BRACKET = 15,
  INCREMENT = 16,
  PLUS = 17,
  DECREMENT = 18,
  ASTERISK = 19,
  SLASH = 20,
  PERCENT = 21,
  EQUAL_TO = 22,
  EQUAL = 23,
  NOT_EQUAL = 24,
  NOT = 25,
  LESS_THAN_OR_EQUAL_TO = 26,
  LEFT_SHIFT = 27,
  LESS_THAN = 28,
  GREATER_THAN_OR_EQUAL_TO = 29,
  RIGHT_SHIFT = 30,
  GREATER_THAN = 31,
  AND = 32,
  BITWISE_AND = 33,
  OR = 34,
  BITWISE_OR = 35,
  XOR = 36,
  BITWISE_NOT = 37,
  SEMICOLON = 38,
  DECIMAL = 39,
  INT = 40,
  MINUS = 41,
  CHAR = 42,
  STRING = 43,
  ID = 44,
  UNKNOWN = 45,
  NEOF = 46,
};
// END_TOKEN_TYPE_TARGET

    /**
     * @brief Struktur yang menyimpan data dari setiap token.
     */
    struct Data
    {
        /**
         * @brief Konstruktor untuk inisialisasi Data.
         * @param type Jenis token.
         * @param pattern Pola regex yang digunakan untuk mencocokkan token.
         * @param skip Menentukan apakah token ini harus dilewati saat pemrosesan.
         */
        Data(const Type& type, std::regex pattern, const bool& skip) : type(type), pattern(std::move(pattern)), skip(skip) {}

        Type type;          ///< Jenis token
        std::regex pattern; ///< Pola regex untuk mencocokkan token
        bool skip = false;  ///< Menentukan apakah token ini harus dilewati saat pemrosesan
    };

    Location location;   ///< Lokasi token dalam file
    std::string content; ///< Konten dari token
    Type type = UNKNOWN; ///< Jenis token

    /**
     * @brief Operator untuk mencetak NToken ke output stream.
     * @param os Output stream yang digunakan untuk mencetak.
     * @param token Token yang akan dicetak.
     * @return Referensi ke output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const NToken& token)
    {
        os << token.location << " [" << token.type << "] " << token.content;
        return os;
    } // operator<<

}; // struct NToken

/**
 * @brief Data statis yang berisi informasi tentang semua jenis token dan pola regex-nya.
 */
// TOKEN_DATA_TARGET
static const std::array<NToken::Data, 47> tokenData = {
  NToken::Data{NToken::NEWLINE, std::regex(R"(^[\n])"), true},
  NToken::Data{NToken::WHITESPACE, std::regex(R"(^\s)"), true},
  NToken::Data{NToken::SINGLE_LINE_COMMENT, std::regex(R"(^\/\/.*)"), true},
  NToken::Data{NToken::MULTI_LINE_COMMENT, std::regex(R"(^\/\*(.|\n)*?\*\/)"), true},
  NToken::Data{NToken::LOAD_FILE_KEYWORD, std::regex(R"(^muat)"), false},
  NToken::Data{NToken::INT_KEYWORD, std::regex(R"(^bul)"), false},
  NToken::Data{NToken::DECIMAL_KEYWORD, std::regex(R"(^des)"), false},
  NToken::Data{NToken::STRING_KEYWORD, std::regex(R"(^teks)"), false},
  NToken::Data{NToken::CHAR_KEYWORD, std::regex(R"(^kar)"), false},
  NToken::Data{NToken::BOOLEAN_KEYWORD, std::regex(R"(^log)"), false},
  NToken::Data{NToken::TRUE_KEYWORD, std::regex(R"(^benar)"), false},
  NToken::Data{NToken::FALSE_KEYWORD, std::regex(R"(^salah)"), false},
  NToken::Data{NToken::OPEN_CURLY_BRACKET, std::regex(R"(^[{])"), false},
  NToken::Data{NToken::CLOSE_CURLY_BRACKET, std::regex(R"(^[}])"), false},
  NToken::Data{NToken::OPEN_ROUND_BRACKET, std::regex(R"(^[(])"), false},
  NToken::Data{NToken::CLOSE_ROUND_BRACKET, std::regex(R"(^[)])"), false},
  NToken::Data{NToken::INCREMENT, std::regex(R"(^\+\+)"), false},
  NToken::Data{NToken::PLUS, std::regex(R"(^\+)"), false},
  NToken::Data{NToken::DECREMENT, std::regex(R"(^--)"), false},
  NToken::Data{NToken::ASTERISK, std::regex(R"(^\*)"), false},
  NToken::Data{NToken::SLASH, std::regex(R"(^\/)"), false},
  NToken::Data{NToken::PERCENT, std::regex(R"(^%)"), false},
  NToken::Data{NToken::EQUAL_TO, std::regex(R"(^==)"), false},
  NToken::Data{NToken::EQUAL, std::regex(R"(^=)"), false},
  NToken::Data{NToken::NOT_EQUAL, std::regex(R"(^!=)"), false},
  NToken::Data{NToken::NOT, std::regex(R"(^!)"), false},
  NToken::Data{NToken::LESS_THAN_OR_EQUAL_TO, std::regex(R"(^<=)"), false},
  NToken::Data{NToken::LEFT_SHIFT, std::regex(R"(^<<)"), false},
  NToken::Data{NToken::LESS_THAN, std::regex(R"(^<)"), false},
  NToken::Data{NToken::GREATER_THAN_OR_EQUAL_TO, std::regex(R"(^>=)"), false},
  NToken::Data{NToken::RIGHT_SHIFT, std::regex(R"(^>>)"), false},
  NToken::Data{NToken::GREATER_THAN, std::regex(R"(^>)"), false},
  NToken::Data{NToken::AND, std::regex(R"(^&&)"), false},
  NToken::Data{NToken::BITWISE_AND, std::regex(R"(^&)"), false},
  NToken::Data{NToken::OR, std::regex(R"(^\|\|)"), false},
  NToken::Data{NToken::BITWISE_OR, std::regex(R"(^\|)"), false},
  NToken::Data{NToken::XOR, std::regex(R"(^\^)"), false},
  NToken::Data{NToken::BITWISE_NOT, std::regex(R"(^~)"), false},
  NToken::Data{NToken::SEMICOLON, std::regex(R"(^;)"), false},
  NToken::Data{NToken::DECIMAL, std::regex(R"(^-?[0-9]+.[0-9]+)"), false},
  NToken::Data{NToken::INT, std::regex(R"(^-?[0-9][0-9]*)"), false},
  NToken::Data{NToken::MINUS, std::regex(R"(^-)"), false},
  NToken::Data{NToken::CHAR, std::regex(R"(^'.[^']')"), false},
  NToken::Data{NToken::STRING, std::regex(R"(^".[^"]*")"), false},
  NToken::Data{NToken::ID, std::regex(R"(^[a-zA-Z][a-zA-Z0-9_]*)"), false},
  NToken::Data{NToken::UNKNOWN, std::regex(R"(^.)"), false},
  NToken::Data{NToken::NEOF, std::regex(R"(^\0)"), false},
};
// END_TOKEN_DATA_TARGET

} // namespace nlexer

#endif // NTOKEN_H