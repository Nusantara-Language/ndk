#pragma once

#include <memory>
#include <string>
#include <vector>

#include "listener/listener.hpp"

#include "visitor/visitor.hpp"

#include "token/token.hpp"

#include "parser/parser_exception.hpp"

#include "node/node.hpp"

// Namespace
namespace nusantara {

  class Parser {
    public:
      // Constructor
      explicit Parser(
        const bool &ast
      ): ast(ast) {}

      explicit Parser(): Parser(false) {}

      // Function
      auto parsing() -> void;
      [[nodiscard]] auto getResult() const -> const std::unique_ptr<Node>&;
      auto print() -> void;
      auto setTokens(const std::vector<nusantara::Token>& tokens) -> void;

    private:
      // Variabel
      size_t current = 0;
      std::vector<nusantara::Token> tokens;
      std::unique_ptr<Node> parsingResult;
      bool ast;

      // Pesan error ketika parsing gagal
      static auto error(
        const nusantara::Token &token, 
        const std::string &message
      ) -> ParserException;

      // Memanggil token saat ini tanpa memajukan.
      [[nodiscard]] auto peek() const -> const nusantara::Token &;

      // Memeriksa apakah sudah sampe akhir token
      [[nodiscard]] auto isAtEnd() const -> bool;

      // Mengecek apakah token saat ini memiliki tipe tertentu tanpa memajukan token
      [[nodiscard]] auto check(const nusantara::TokenType &type) const -> bool;

      // Mengambil token terakhir yang sudah di prosess
      auto previous() -> const nusantara::Token &;

      // Maju ke token berikutnya dan mengambil token sebelum nya
      auto advance() -> const nusantara::Token &;

      // Membaca token saat ini dan maju ke token berikut nya
      auto consume(
        const nusantara::TokenType &type, 
        const std::string &errorMessage
      ) -> const nusantara::Token &;

      // Memerikas apakah token saat ini cocok dengan salah satu tipe token yang diberikan
      auto match(const std::vector<nusantara::TokenType> &types) -> bool;

      // * Parse Core
      auto parsePernyataanEkspresi() -> std::unique_ptr<Node>;

      // * Parse Fungsi Group
      auto parsePanggilFungsi() -> std::unique_ptr<Node>;
      auto parseTempatParameterPanggilFungsi() -> std::unique_ptr<Node>;
  };

}  // namespace nusantara
