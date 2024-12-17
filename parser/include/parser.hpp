// Header guard
#ifndef PARSER_HPP
#define PARSER_HPP

// Include STD C++
#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Include project file
#include "lexer.hpp"
#include "listener.hpp"
#include "visitor.hpp"

// Namespace
namespace parser {

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
        const lexer::Token &token
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
      [[nodiscard]] auto getToken() const -> const std::optional<lexer::Token>&;
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
      std::optional<lexer::Token> token;
      std::vector<std::unique_ptr<Node>> children;
  };

  class ParseNode {
    public:
      // Constructor
      explicit ParseNode(
        std::vector<lexer::Token> tokens
      ): tokens(std::move(tokens)) {}

      // Function
      auto parse() -> std::unique_ptr<Node>;

    private:
      // Variabel
      size_t current = 0;
      std::vector<lexer::Token> tokens;

      // Pesan error ketika parsing gagal
      static auto error(
        const lexer::Token &token, 
        const std::string &message
      ) -> ParserException;

      // Memanggil token saat ini tanpa memajukan.
      [[nodiscard]] auto peek() const -> const lexer::Token &;

      // Memeriksa apakah sudah sampe akhir token
      [[nodiscard]] auto isAtEnd() const -> bool;

      // Mengecek apakah token saat ini memiliki tipe tertentu tanpa memajukan token
      [[nodiscard]] auto check(const lexer::TokenType &type) const -> bool;

      // Mengambil token terakhir yang sudah di prosess
      auto previous() -> const lexer::Token &;

      // Maju ke token berikutnya dan mengambil token sebelum nya
      auto advance() -> const lexer::Token &;

      // Membaca token saat ini dan maju ke token berikut nya
      auto consume(
        const lexer::TokenType &type, 
        const std::string &errorMessage
      ) -> const lexer::Token &;

      // Memerikas apakah token saat ini cocok dengan salah satu tipe token yang diberikan
      auto match(const std::vector<lexer::TokenType> &types) -> bool;

      // * Parse Core
      auto parsePernyataanEkspresi() -> std::unique_ptr<Node>;

      // * Parse Fungsi Group
      auto parsePanggilFungsi() -> std::unique_ptr<Node>;
      auto parseTempatParameterPanggilFungsi() -> std::unique_ptr<Node>;
  };

  // Function
  auto nodeTypeToString(const NodeType &type) -> std::string;

  void coutNode(const Node &root, int initialSpace);

}  // namespace parser

#endif
