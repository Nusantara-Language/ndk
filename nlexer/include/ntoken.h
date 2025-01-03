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

    // NTKN_TYPE_TARGET

    enum Type
    {
        NEWLINE_TOKEN = 0,
        WHITESPACE_TOKEN = 1,
        SINGLE_LINE_COMMENT_TOKEN = 2,
        MULTI_LINE_COMMENT_TOKEN = 3,
        LOAD_FILE_TOKEN = 4,
        TYPE_BILANGAN_BULAT_TOKEN = 5,
        TYPE_BILANGAN_DESIMAL_TOKEN = 6,
        TYPE_TEKS_TOKEN = 7,
        TYPE_KARAKTER_TOKEN = 8,
        TYPE_LOGIKA_TOKEN = 9,
        VALUE_BENAR_TOKEN = 10,
        VALUE_SALAH_TOKEN = 11,
        BRACKET_OPEN_CURLY = 12,
        BRACKET_CLOSE_CURLY = 13,
        BRACKET_OPEN_ROUND = 14,
        BRACKET_CLOSE_ROUND = 15,
        INCREMENT_OP = 16,
        DECREMENT_OP = 17,
        ADDITION_ASSIGN_OP = 18,
        SUBTRACTION_ASSIGN_OP = 19,
        MULTIPLICATION_ASSIGN_OP = 20,
        DIVISION_ASSIGN_OP = 21,
        MODULO_ASSIGN_OP = 22,
        BITWISE_LEFT_SHIFT_ASSIGN_OP = 23,
        BITWISE_RIGHT_SHIFT_ASSIGN_OP = 24,
        BITWISE_AND_ASSIGN_OP = 25,
        BITWISE_OR_ASSIGN_OP = 26,
        BITWISE_XOR_ASSIGN_OP = 27,
        BILANGAN_DESIMAL_LITERAL = 28,
        BILANGAN_BULAT_LITERAL = 29,
        PLUS_OP = 30,
        MINUS_OP = 31,
        ASTERISK_OP = 32,
        SLASH_OP = 33,
        PERCENT_OP = 34,
        EQUAL_TO_OP = 35,
        NOT_EQUAL_OP = 36,
        LESS_THAN_OR_EQUAL_TO_OP = 37,
        GREATER_THAN_OR_EQUAL_TO_OP = 38,
        LESS_THAN_OP = 39,
        GREATER_THAN_OP = 40,
        LOGICAL_NOT_OP = 41,
        LOGICAL_AND_OP = 42,
        LOGICAL_OR_OP = 43,
        BITWISE_LEFT_SHIFT_OP = 44,
        BITWISE_RIGHT_SHIFT_OP = 45,
        BITWISE_AND_OP = 46,
        BITWISE_OR_OP = 47,
        BITWISE_XOR_OP = 48,
        BITWISE_NOT_OP = 49,
        COMA = 50,
        ASSIGNMENT_OP = 51,
        SEMICOLON_TOKEN = 52,
        KARAKTER_LITERAL = 53,
        TEKS_LITERAL = 54,
        IDENTIFIER_TOKEN = 55,
        UNKNOWN_TOKEN = 56,
        NEOF_TOKEN = 57,
    };

    // END_NTKN_TYPE_TARGET

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

    Location location;         ///< Lokasi token dalam file
    std::string content;       ///< Konten dari token
    Type type = UNKNOWN_TOKEN; ///< Jenis token

    /**
     * @brief Operator untuk mencetak NToken ke output stream.
     * @param os Output stream yang digunakan untuk mencetak.
     * @param token Token yang akan dicetak.
     * @return Referensi ke output stream.
     */
    // NTKN_COUT_SUPPORT_TARGET
    friend std::ostream& operator<<(std::ostream& os, const NToken& token)
    {
        os << token.location << " [";
        switch (token.type)
        {
        case NToken::NEWLINE_TOKEN:
            os << "NEWLINE_TOKEN";
            break;
        case NToken::WHITESPACE_TOKEN:
            os << "WHITESPACE_TOKEN";
            break;
        case NToken::SINGLE_LINE_COMMENT_TOKEN:
            os << "SINGLE_LINE_COMMENT_TOKEN";
            break;
        case NToken::MULTI_LINE_COMMENT_TOKEN:
            os << "MULTI_LINE_COMMENT_TOKEN";
            break;
        case NToken::LOAD_FILE_TOKEN:
            os << "LOAD_FILE_TOKEN";
            break;
        case NToken::TYPE_BILANGAN_BULAT_TOKEN:
            os << "TYPE_BILANGAN_BULAT_TOKEN";
            break;
        case NToken::TYPE_BILANGAN_DESIMAL_TOKEN:
            os << "TYPE_BILANGAN_DESIMAL_TOKEN";
            break;
        case NToken::TYPE_TEKS_TOKEN:
            os << "TYPE_TEKS_TOKEN";
            break;
        case NToken::TYPE_KARAKTER_TOKEN:
            os << "TYPE_KARAKTER_TOKEN";
            break;
        case NToken::TYPE_LOGIKA_TOKEN:
            os << "TYPE_LOGIKA_TOKEN";
            break;
        case NToken::VALUE_BENAR_TOKEN:
            os << "VALUE_BENAR_TOKEN";
            break;
        case NToken::VALUE_SALAH_TOKEN:
            os << "VALUE_SALAH_TOKEN";
            break;
        case NToken::BRACKET_OPEN_CURLY:
            os << "BRACKET_OPEN_CURLY";
            break;
        case NToken::BRACKET_CLOSE_CURLY:
            os << "BRACKET_CLOSE_CURLY";
            break;
        case NToken::BRACKET_OPEN_ROUND:
            os << "BRACKET_OPEN_ROUND";
            break;
        case NToken::BRACKET_CLOSE_ROUND:
            os << "BRACKET_CLOSE_ROUND";
            break;
        case NToken::INCREMENT_OP:
            os << "INCREMENT_OP";
            break;
        case NToken::DECREMENT_OP:
            os << "DECREMENT_OP";
            break;
        case NToken::ADDITION_ASSIGN_OP:
            os << "ADDITION_ASSIGN_OP";
            break;
        case NToken::SUBTRACTION_ASSIGN_OP:
            os << "SUBTRACTION_ASSIGN_OP";
            break;
        case NToken::MULTIPLICATION_ASSIGN_OP:
            os << "MULTIPLICATION_ASSIGN_OP";
            break;
        case NToken::DIVISION_ASSIGN_OP:
            os << "DIVISION_ASSIGN_OP";
            break;
        case NToken::MODULO_ASSIGN_OP:
            os << "MODULO_ASSIGN_OP";
            break;
        case NToken::BITWISE_LEFT_SHIFT_ASSIGN_OP:
            os << "BITWISE_LEFT_SHIFT_ASSIGN_OP";
            break;
        case NToken::BITWISE_RIGHT_SHIFT_ASSIGN_OP:
            os << "BITWISE_RIGHT_SHIFT_ASSIGN_OP";
            break;
        case NToken::BITWISE_AND_ASSIGN_OP:
            os << "BITWISE_AND_ASSIGN_OP";
            break;
        case NToken::BITWISE_OR_ASSIGN_OP:
            os << "BITWISE_OR_ASSIGN_OP";
            break;
        case NToken::BITWISE_XOR_ASSIGN_OP:
            os << "BITWISE_XOR_ASSIGN_OP";
            break;
        case NToken::BILANGAN_DESIMAL_LITERAL:
            os << "BILANGAN_DESIMAL_LITERAL";
            break;
        case NToken::BILANGAN_BULAT_LITERAL:
            os << "BILANGAN_BULAT_LITERAL";
            break;
        case NToken::PLUS_OP:
            os << "PLUS_OP";
            break;
        case NToken::MINUS_OP:
            os << "MINUS_OP";
            break;
        case NToken::ASTERISK_OP:
            os << "ASTERISK_OP";
            break;
        case NToken::SLASH_OP:
            os << "SLASH_OP";
            break;
        case NToken::PERCENT_OP:
            os << "PERCENT_OP";
            break;
        case NToken::EQUAL_TO_OP:
            os << "EQUAL_TO_OP";
            break;
        case NToken::NOT_EQUAL_OP:
            os << "NOT_EQUAL_OP";
            break;
        case NToken::LESS_THAN_OR_EQUAL_TO_OP:
            os << "LESS_THAN_OR_EQUAL_TO_OP";
            break;
        case NToken::GREATER_THAN_OR_EQUAL_TO_OP:
            os << "GREATER_THAN_OR_EQUAL_TO_OP";
            break;
        case NToken::LESS_THAN_OP:
            os << "LESS_THAN_OP";
            break;
        case NToken::GREATER_THAN_OP:
            os << "GREATER_THAN_OP";
            break;
        case NToken::LOGICAL_NOT_OP:
            os << "LOGICAL_NOT_OP";
            break;
        case NToken::LOGICAL_AND_OP:
            os << "LOGICAL_AND_OP";
            break;
        case NToken::LOGICAL_OR_OP:
            os << "LOGICAL_OR_OP";
            break;
        case NToken::BITWISE_LEFT_SHIFT_OP:
            os << "BITWISE_LEFT_SHIFT_OP";
            break;
        case NToken::BITWISE_RIGHT_SHIFT_OP:
            os << "BITWISE_RIGHT_SHIFT_OP";
            break;
        case NToken::BITWISE_AND_OP:
            os << "BITWISE_AND_OP";
            break;
        case NToken::BITWISE_OR_OP:
            os << "BITWISE_OR_OP";
            break;
        case NToken::BITWISE_XOR_OP:
            os << "BITWISE_XOR_OP";
            break;
        case NToken::BITWISE_NOT_OP:
            os << "BITWISE_NOT_OP";
            break;
        case NToken::COMA:
            os << "COMA";
            break;
        case NToken::ASSIGNMENT_OP:
            os << "ASSIGNMENT_OP";
            break;
        case NToken::SEMICOLON_TOKEN:
            os << "SEMICOLON_TOKEN";
            break;
        case NToken::KARAKTER_LITERAL:
            os << "KARAKTER_LITERAL";
            break;
        case NToken::TEKS_LITERAL:
            os << "TEKS_LITERAL";
            break;
        case NToken::IDENTIFIER_TOKEN:
            os << "IDENTIFIER_TOKEN";
            break;
        case NToken::UNKNOWN_TOKEN:
            os << "UNKNOWN_TOKEN";
            break;
        case NToken::NEOF_TOKEN:
            os << "NEOF_TOKEN";
            break;
        default:
            os << token.type;
            break;
        }
        os << "] " << token.content;
        return os;
    }

    // END_NTKN_COUT_SUPPORT_TARGET

}; // struct NToken

/**
 * @brief Data statis yang berisi informasi tentang semua jenis token dan pola regex-nya.
 */
// NTKN_DATA_TARGET

static const std::array<NToken::Data, 58> tokenData = {
    NToken::Data{NToken::NEWLINE_TOKEN, std::regex(R"(^\n)"), true},
    NToken::Data{NToken::WHITESPACE_TOKEN, std::regex(R"(^\s)"), true},
    NToken::Data{NToken::SINGLE_LINE_COMMENT_TOKEN, std::regex(R"(^\/\/.*)"), true},
    NToken::Data{NToken::MULTI_LINE_COMMENT_TOKEN, std::regex(R"(^\/\*(.|\n)*?\*\/)"), true},
    NToken::Data{NToken::LOAD_FILE_TOKEN, std::regex(R"(^muat)"), false},
    NToken::Data{NToken::TYPE_BILANGAN_BULAT_TOKEN, std::regex(R"(^bul)"), false},
    NToken::Data{NToken::TYPE_BILANGAN_DESIMAL_TOKEN, std::regex(R"(^des)"), false},
    NToken::Data{NToken::TYPE_TEKS_TOKEN, std::regex(R"(^teks)"), false},
    NToken::Data{NToken::TYPE_KARAKTER_TOKEN, std::regex(R"(^kar)"), false},
    NToken::Data{NToken::TYPE_LOGIKA_TOKEN, std::regex(R"(^log)"), false},
    NToken::Data{NToken::VALUE_BENAR_TOKEN, std::regex(R"(^benar)"), false},
    NToken::Data{NToken::VALUE_SALAH_TOKEN, std::regex(R"(^salah)"), false},
    NToken::Data{NToken::BRACKET_OPEN_CURLY, std::regex(R"(^[{])"), false},
    NToken::Data{NToken::BRACKET_CLOSE_CURLY, std::regex(R"(^[}])"), false},
    NToken::Data{NToken::BRACKET_OPEN_ROUND, std::regex(R"(^[(])"), false},
    NToken::Data{NToken::BRACKET_CLOSE_ROUND, std::regex(R"(^[)])"), false},
    NToken::Data{NToken::INCREMENT_OP, std::regex(R"(^\+\+)"), false},
    NToken::Data{NToken::DECREMENT_OP, std::regex(R"(^--)"), false},
    NToken::Data{NToken::ADDITION_ASSIGN_OP, std::regex(R"(^\+=)"), false},
    NToken::Data{NToken::SUBTRACTION_ASSIGN_OP, std::regex(R"(^-=)"), false},
    NToken::Data{NToken::MULTIPLICATION_ASSIGN_OP, std::regex(R"(^\*=)"), false},
    NToken::Data{NToken::DIVISION_ASSIGN_OP, std::regex(R"(^\/=)"), false},
    NToken::Data{NToken::MODULO_ASSIGN_OP, std::regex(R"(^%=)"), false},
    NToken::Data{NToken::BITWISE_LEFT_SHIFT_ASSIGN_OP, std::regex(R"(^<<=)"), false},
    NToken::Data{NToken::BITWISE_RIGHT_SHIFT_ASSIGN_OP, std::regex(R"(^>>=)"), false},
    NToken::Data{NToken::BITWISE_AND_ASSIGN_OP, std::regex(R"(^&=)"), false},
    NToken::Data{NToken::BITWISE_OR_ASSIGN_OP, std::regex(R"(^\|=)"), false},
    NToken::Data{NToken::BITWISE_XOR_ASSIGN_OP, std::regex(R"(^\^=)"), false},
    NToken::Data{NToken::BILANGAN_DESIMAL_LITERAL, std::regex(R"(^-?[0-9]+\.[0-9]+)"), false},
    NToken::Data{NToken::BILANGAN_BULAT_LITERAL, std::regex(R"(^-?[0-9][0-9]*)"), false},
    NToken::Data{NToken::PLUS_OP, std::regex(R"(^\+)"), false},
    NToken::Data{NToken::MINUS_OP, std::regex(R"(^-)"), false},
    NToken::Data{NToken::ASTERISK_OP, std::regex(R"(^\*)"), false},
    NToken::Data{NToken::SLASH_OP, std::regex(R"(^\/)"), false},
    NToken::Data{NToken::PERCENT_OP, std::regex(R"(^%)"), false},
    NToken::Data{NToken::EQUAL_TO_OP, std::regex(R"(^==)"), false},
    NToken::Data{NToken::NOT_EQUAL_OP, std::regex(R"(^!=)"), false},
    NToken::Data{NToken::LESS_THAN_OR_EQUAL_TO_OP, std::regex(R"(^<=)"), false},
    NToken::Data{NToken::GREATER_THAN_OR_EQUAL_TO_OP, std::regex(R"(^>=)"), false},
    NToken::Data{NToken::LESS_THAN_OP, std::regex(R"(^<)"), false},
    NToken::Data{NToken::GREATER_THAN_OP, std::regex(R"(^>)"), false},
    NToken::Data{NToken::LOGICAL_NOT_OP, std::regex(R"(^!)"), false},
    NToken::Data{NToken::LOGICAL_AND_OP, std::regex(R"(^&&)"), false},
    NToken::Data{NToken::LOGICAL_OR_OP, std::regex(R"(^\|\|)"), false},
    NToken::Data{NToken::BITWISE_LEFT_SHIFT_OP, std::regex(R"(^<<)"), false},
    NToken::Data{NToken::BITWISE_RIGHT_SHIFT_OP, std::regex(R"(^>>)"), false},
    NToken::Data{NToken::BITWISE_AND_OP, std::regex(R"(^&)"), false},
    NToken::Data{NToken::BITWISE_OR_OP, std::regex(R"(^\|)"), false},
    NToken::Data{NToken::BITWISE_XOR_OP, std::regex(R"(^\^)"), false},
    NToken::Data{NToken::BITWISE_NOT_OP, std::regex(R"(^~)"), false},
    NToken::Data{NToken::COMA, std::regex(R"(^,)"), false},
    NToken::Data{NToken::ASSIGNMENT_OP, std::regex(R"(^=)"), false},
    NToken::Data{NToken::SEMICOLON_TOKEN, std::regex(R"(^;)"), false},
    NToken::Data{NToken::KARAKTER_LITERAL, std::regex(R"(^'(.|[^'])')"), false},
    NToken::Data{NToken::TEKS_LITERAL, std::regex(R"(^".[^"]*")"), false},
    NToken::Data{NToken::IDENTIFIER_TOKEN, std::regex(R"(^[a-zA-Z][a-zA-Z0-9_]*)"), false},
    NToken::Data{NToken::UNKNOWN_TOKEN, std::regex(R"(^.)"), false},
    NToken::Data{NToken::NEOF_TOKEN, std::regex(R"(^\0)"), false},
};
// END_NTKN_DATA_TARGET

} // namespace nlexer

#endif // NTOKEN_H