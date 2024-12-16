#pragma once

#include "lexer.h"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace Parser {

    enum NodeType {
        TOKEN,
        AWAL,
        PERNYATAAN,
        DEKLARASI_FUNGSI,
        PARAMETER_DEKLARASI_FUNGSI,
        BLOK_KODE,
    };

    std::string nodeTypeToString(const NodeType &type);

    class Node {
        public:
            NodeType type;
            std::optional<Lexer::Token> token;
            std::vector<std::unique_ptr<Node>> children;

            Node(const NodeType& type, const Lexer::Token& token): type(type), token(token) {}
            Node(const NodeType& type): type(type), token(std::nullopt) {}

            void addChild(std::unique_ptr<Node> node);
    };

    void coutNode(const Node& node, int space);

    struct ParserException : public std::runtime_error {
        ParserException(const std::string& message): std::runtime_error(message) {}
    };

    struct ParseErrorLocation {
        std::string filename;
        int row;
        int startColumn;
        int endColumn;
    };

    struct ParseError {
        std::vector<ParseErrorLocation> locations;
        std::string message;  
    };

    class ParseErrorManager {
        public:
            ParseErrorManager();
            void addError(const Lexer::Token& token, const std::string& message);
        private:
            std::vector<ParseError> errors;
    };

    class ParseNode {
        public:
            ParseNode(std::vector<Lexer::Token> tokens): tokens(std::move(tokens)) {}
            std::unique_ptr<Node> parse();
        private:
            size_t current = 0;
            std::vector<Lexer::Token> tokens;
            
            // Pesan error ketika parsing gagal
            std::string error(const Lexer::Token& token, const std::string& message);

            // Memanggil token saat ini tanpa memajukan.
            const Lexer::Token& peek() const;

            // Memeriksa apakah sudah sampe akhir token
            const bool isAtEnd() const;

            // Mengecek apakah token saat ini memiliki tipe tertentu tanpa memajukan token
            const bool check(const Lexer::TokenType& type);

            // Mengambil token terakhir yang sudah di prosess
            const Lexer::Token& previous();

            // Maju ke token berikutnya dan mengambil token sebelum nya
            const Lexer::Token& advance();

            // Membaca token saat ini dan maju ke token berikut nya
            const Lexer::Token& consume(const Lexer::TokenType& type, const std::string& errorMessage);

            // Memerikas apakah token saat ini cocok dengan salah satu tipe token yang diberikan
            const bool match(const std::vector<Lexer::TokenType>& types);

            // * Parse Core
            std::unique_ptr<Node> parsePernyataan();

            // * Parse Fungsi Group
            std::unique_ptr<Node> parseDeklarasiFungsi();
            std::unique_ptr<Node> parseParameterDeklarasiFungsi();
            
            // * Parse Blok Kode Group
            std::unique_ptr<Node> parseBlokKode();
            
    };
}