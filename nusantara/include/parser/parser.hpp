#pragma once

// Include STD C++
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

// Include project file
#include "lexer/lexer.hpp"
#include "listener/listener.hpp"
#include "visitor/visitor.hpp"

// Namespace
namespace nusantara {

  // Enum
  enum NodeType {
    TOKEN,
    AWAL,
    PERNYATAAN_EKSPRESI,
    PANGGIL_FUNGSI,
    TEMPAT_PARAMETER_PANGGIL_FUNGSI,
  };

  // Struct
  struct ParserException : public std::runtime_error {
    // Constructor
    explicit ParserException(
      const std::string &message
    ): 
    std::runtime_error(message) 
    {}
  };

  // Class
  class Node {
    public:
      // Constructor
      Node(Node &&) = default;

      Node(const Node& other);

      Node(
        const NodeType &type, 
        const nusantara::Token &token
      ): 
      type(type), 
      token(token) 
      {}

      explicit Node(const NodeType &type) : type(type), token(std::nullopt) {}

      // Destructor
      ~Node() = default;

      // Operator
      auto operator=(const Node &) -> Node & = default;
      auto operator=(Node &&) -> Node & = default;
      auto operator<(const Node &other) const -> bool;

      // Getter
      [[nodiscard]] auto getType() const -> const NodeType&;
      [[nodiscard]] auto getToken() const -> const std::optional<nusantara::Token>&;
      [[nodiscard]] auto getChildren() const -> const std::vector<std::unique_ptr<Node>>&;

      // Function
      template<typename T>
      void accept(INodeVisitor<T>& visitor) const {
        switch (this->type) {
          case NodeType::AWAL:
              visitor.visitAwalNode(*this);
              break;
          case NodeType::PERNYATAAN_EKSPRESI:
              visitor.visitPernyataanEkspresiNode(*this);
              break;
          case NodeType::PANGGIL_FUNGSI:
              visitor.visitPanggilFungsiNode(*this);
              break;
          case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
              visitor.visitTempatParameterPanggilFungsiNode(*this);
              break;
          case NodeType::TOKEN:
              visitor.visitTokenNode(*this);
              break;
          default:
              std::cerr << "Tipe node tidak dapat di kunjungi." << std::endl;
              break;
        }

        for(const auto& child : children) {
            child->accept(visitor);
        }
      }

      void accept(INodeListener& listener) const;

      void addChild(std::unique_ptr<Node> node);

    private:
      NodeType type;
      std::optional<nusantara::Token> token;
      std::vector<std::unique_ptr<Node>> children;
  };

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

  // Function
  auto nodeTypeToString(const NodeType &type) -> std::string;

  void printNode(const Node &root, int initialSpace);

}  // namespace nusantara
