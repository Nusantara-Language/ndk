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
    enum Type
    {
        NEWLINE = 0,
        WHITESPACE = 1,
        SINGLE_LINE_COMMENT = 2,
        MULTI_LINE_COMMENT = 3,
        LOAD_FILE_KEYWORD = 4,
        INPUT_KEYWORD = 5,
        OPEN_CURLY_BRACKET = 6,
        CLOSE_CURLY_BRACKET = 7,
        INCREMENT = 8,
        PLUS = 9,
        RETURN_SIGN = 10,
        DECREMENT = 11,
        MINUS = 12,
        ASTERISK = 13,
        SLASH = 14,
        PERCENT = 15,
        EQUAL_TO = 16,
        EQUAL = 17,
        NOT_EQUAL = 18,
        NOT = 19,
        LESS_THAN_OR_EQUAL_TO = 20,
        LEFT_SHIFT = 21,
        LESS_THAN = 22,
        GREATER_THAN_OR_EQUAL_TO = 23,
        RIGHT_SHIFT = 24,
        GREATER_THAN = 25,
        AND = 26,
        BITWISE_AND = 27,
        OR = 28,
        BITWISE_OR = 29,
        XOR = 30,
        BITWISE_NOT = 31,
        INT = 32,
        STRING = 33,
        ID = 34,
        UNKNOWN = 35,
        NEOF = 36,
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
        inline Data(const Type& type, std::regex pattern, const bool& skip) : type(type), pattern(std::move(pattern)), skip(skip) {}

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
    inline friend std::ostream& operator<<(std::ostream& os, const NToken& token)
    {
        os << token.location << " [" << token.type << "] " << token.content;
        return os;
    } // operator<<

}; // struct NToken

/**
 * @brief Data statis yang berisi informasi tentang semua jenis token dan pola regex-nya.
 */
// TOKEN_DATA_TARGET
inline static const std::array<NToken::Data, 37> tokenData = {
    NToken::Data{NToken::NEWLINE, std::regex(R"(^[\n])"), true},
    NToken::Data{NToken::WHITESPACE, std::regex(R"(^\s)"), true},
    NToken::Data{NToken::SINGLE_LINE_COMMENT, std::regex(R"(^\/\/.*)"), false},
    NToken::Data{NToken::MULTI_LINE_COMMENT, std::regex(R"(^\/\*(.|\n)*?\*\/)"), false},
    NToken::Data{NToken::LOAD_FILE_KEYWORD, std::regex(R"(^muat)"), false},
    NToken::Data{NToken::INPUT_KEYWORD, std::regex(R"(^masukkan)"), false},
    NToken::Data{NToken::OPEN_CURLY_BRACKET, std::regex(R"(^[{])"), false},
    NToken::Data{NToken::CLOSE_CURLY_BRACKET, std::regex(R"(^[}])"), false},
    NToken::Data{NToken::INCREMENT, std::regex(R"(^\+\+)"), false},
    NToken::Data{NToken::PLUS, std::regex(R"(^\+)"), false},
    NToken::Data{NToken::RETURN_SIGN, std::regex(R"(^->)"), false},
    NToken::Data{NToken::DECREMENT, std::regex(R"(^--)"), false},
    NToken::Data{NToken::MINUS, std::regex(R"(^-)"), false},
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
    NToken::Data{NToken::INT, std::regex(R"(^[0-9][0-9]*)"), false},
    NToken::Data{NToken::STRING, std::regex(R"(^(".[^"]*"|'.[^']*'))"), false},
    NToken::Data{NToken::ID, std::regex(R"(^[a-zA-Z][a-zA-Z0-9_]*)"), false},
    NToken::Data{NToken::UNKNOWN, std::regex(R"(^.)"), false},
    NToken::Data{NToken::NEOF, std::regex(R"(^\0)"), false},
};
// END_TOKEN_DATA_TARGET

} // namespace nlexer

#endif // NTOKEN_H