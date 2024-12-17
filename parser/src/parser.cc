// Include STD C++
#include <algorithm>
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// Include project file
#include "lexer.hpp"
#include "parser.hpp"

// Class Node
Parser::Node::Node(const Node& other): type(other.type), token(other.token) {
  for(const auto& child : other.children) {
    children.push_back(std::make_unique<Node>(*child));
  }
}

auto Parser::Node::getType() const -> const NodeType & { return this->type; }

auto Parser::Node::getToken() const -> const std::optional<lexer::Token> & {
  return this->token;
}

auto Parser::Node::getChildren() const -> const std::vector<std::unique_ptr<Node>> & {
  return this->children;
}

void Parser::Node::addChild(std::unique_ptr<Node> node) {
  this->children.push_back(std::move(node));
}

auto Parser::Node::operator<(const Node& other) const -> bool {
  bool tokenBoolTemp = false;
  if(this->token && other.token) {
    tokenBoolTemp = this->token->type < other.token->type;
  }
  return this->type < other.type && tokenBoolTemp && (this->children.size() < other.children.size());
}

// Function
auto Parser::nodeTypeToString(const NodeType &type) -> std::string {
  switch(type) {
    case AWAL:
      return "AWAL";
    case PERNYATAAN_EKSPRESI:
      return "PERNYATAAN EKSPRESI";
    case PANGGIL_FUNGSI:
      return "PANGGIL FUNGSI";
    case TEMPAT_PARAMETER_PANGGIL_FUNGSI:
      return "TEMPAT PARAMETER PANGGIL FUNGSI";
    case TOKEN:
      return "TOKEN";
    default:
      std::cerr << "Invalid Node type!" << '\n';
      break;
  }
}

void Parser::coutNode(const Node &root, int initialSpace) { // NOLINT(misc-no-recursion)
  if (root.getType() != NodeType::TOKEN) {
    std::cout << "\033[34m[" << nodeTypeToString(root.getType()) << "]\033[0m\n";
  }

  if (root.getToken()) {
    std::cout << lexer::tokenTypeToString(root.getToken()->type) 
    << ": \033[33m" << root.getToken()->content << "\033[0m\n";
  }

  initialSpace += 3;

  for (const auto &child : root.getChildren()) {
    std::cout << std::string(initialSpace, ' ') << "\033[32m|\033[0m\n";
    std::cout << std::string(initialSpace, ' ') << "\033[32m->\033[0m";
    coutNode(*child, initialSpace);
  }
}

auto Parser::ParseNode::error(
  const lexer::Token &token,
  const std::string &message
) -> ParserException {
  return ParserException(
    std::format(
    "Kesalahan sintaks pada {}:{}:{}\n -> {}",
      token.fileName, 
      token.location.row,
      token.location.column, 
      message
    )
  );
}

auto Parser::ParseNode::peek() const -> const lexer::Token & {
  return this->tokens[this->current];
}

auto Parser::ParseNode::isAtEnd() const -> bool {
  return this->peek().type == lexer::TokenType::akhirDariFile;
}

auto Parser::ParseNode::check(const lexer::TokenType &type) const -> bool {
  if (this->isAtEnd()) {
    return false;
  }
  return this->peek().type == type;
}

auto Parser::ParseNode::previous() -> const lexer::Token & {
  if (this->current == 0) {
    throw std::out_of_range("Berusaha mengakses token sebelum indeks awal.");
  }
  return this->tokens[this->current - 1];
}

auto Parser::ParseNode::advance() -> const lexer::Token & {
  if (!this->isAtEnd()) {
    this->current++;
  }
  return this->previous();
}

auto Parser::ParseNode::consume(
  const lexer::TokenType &type,
  const std::string &errorMessage
) -> const lexer::Token & {
  if (this->check(type)) {
    return this->advance();
  }
  throw Parser::ParseNode::error(this->peek(), errorMessage);
}

auto Parser::ParseNode::match(const std::vector<lexer::TokenType> &types) -> bool {
  if(std::ranges::any_of(
    types,
    [this](auto type) { return this->check(type); }
    )) {
    this->advance();
    return true;
  }
  return false;
}

auto Parser::ParseNode::parse() -> std::unique_ptr<Parser::Node> {
  auto node = Node{NodeType::AWAL};
  while (!this->isAtEnd()) {
    try {
      node.addChild(this->parsePernyataanEkspresi());
    } catch (const ParserException &error) {
      std::cerr << error.what() << "\n\n";
      this->advance();
    }
  }
  return std::make_unique<Node>(std::move(node));
}

// * Parse Core
auto Parser::ParseNode::parsePernyataanEkspresi() -> std::unique_ptr<Parser::Node> { // NOLINT(misc-no-recursion)
  auto node = Node{NodeType::PERNYATAAN_EKSPRESI};

  if(this->check(lexer::TokenType::identifikasi)) {
    node.addChild(this->parsePanggilFungsi()); 
    node.addChild(
      std::make_unique<Node>(
        Node{
          NodeType::TOKEN, 
          this->consume(
            lexer::TokenType::titikKoma,
            "Jangan lupa titik koma."
          )
        }
      )
    );
  }else{
    throw Parser::ParseNode::error(this->peek(), "Pernyataan ekspresi tidak benar.");
  }

  return std::make_unique<Node>(std::move(node));
}

// * Parse Fungsi Group
auto Parser::ParseNode::parsePanggilFungsi() -> std::unique_ptr<Parser::Node> { // NOLINT(misc-no-recursion)
  auto node = Node{NodeType::PANGGIL_FUNGSI};

  node.addChild(
    std::make_unique<Node>(
      Node{
        NodeType::TOKEN, 
        this->consume(
          lexer::TokenType::identifikasi,
          "Nama fungsi belum ditentukan."
        )
      }
    )
  );

  node.addChild(this->parseTempatParameterPanggilFungsi());

  return std::make_unique<Node>(std::move(node));
}

auto Parser::ParseNode::parseTempatParameterPanggilFungsi() -> std::unique_ptr<Parser::Node> {
  auto node = Node{NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI};

  node.addChild(
    std::make_unique<Node>(
      Node{
        NodeType::TOKEN,
        this->consume(
          lexer::TokenType::kurungBulatBuka,
          "Tempat parameter pada fungsi harus ada kurung bulat buka '('."
        )
      }
    )
  );

  node.addChild(
    std::make_unique<Node>(
      Node{
        NodeType::TOKEN,
        this->consume(
          lexer::TokenType::kurungBulatTutup,
          "Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
        )
      }
    )
  );

  return std::make_unique<Node>(std::move(node));
}