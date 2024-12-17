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
#include "visitor.hpp"
#include "lexer.hpp"
#include "listener.hpp"
#include "parser.hpp"

// Class Node
parser::Node::Node(const Node& other): type(other.type), token(other.token) {
  for(const auto& child : other.children) {
    children.push_back(std::make_unique<Node>(*child));
  }
}

auto parser::Node::getType() const -> const NodeType & { return this->type; }

auto parser::Node::getToken() const -> const std::optional<lexer::Token> & {
  return this->token;
}

auto parser::Node::getChildren() const -> const std::vector<std::unique_ptr<Node>> & {
  return this->children;
}

void parser::Node::addChild(std::unique_ptr<Node> node) {
  this->children.push_back(std::move(node));
}

auto parser::Node::operator<(const Node& other) const -> bool {
  bool tokenBoolTemp = false;
  if(this->token && other.token) {
    tokenBoolTemp = this->token->type < other.token->type;
  }
  return this->type < other.type && tokenBoolTemp && (this->children.size() < other.children.size());
}

void parser::Node::accept(INodeListener& listener) const { // NOLINT(misc-no-recursion)
  switch (this->type) {
    case NodeType::AWAL:
        listener.enterAWAL(*this);
        break;
    case NodeType::PERNYATAAN_EKSPRESI:
        listener.enterPernyataanEkspresi(*this);
        break;
    case NodeType::PANGGIL_FUNGSI:
        listener.enterPanggilFungsi(*this);
        break;
    case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
        listener.enterTempatParameterPanggilFungsi(*this);
        break;
    case NodeType::TOKEN:
        listener.enterToken(*this);
        break;
    default:
        std::cerr << "Tipe node tidak dapat di dengar." << std::endl;
        break;
  }

  for(const auto& child : children) {
      child->accept(listener);
  }

  switch (this->type) {
    case NodeType::AWAL:
        listener.exitAWAL(*this);
        break;
    case NodeType::PERNYATAAN_EKSPRESI:
        listener.exitPernyataanEkspresi(*this);
        break;
    case NodeType::PANGGIL_FUNGSI:
        listener.exitPanggilFungsi(*this);
        break;
    case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
        listener.exitTempatParameterPanggilFungsi(*this);
        break;
    case NodeType::TOKEN:
        listener.exitToken(*this);
        break;
    default:
        std::cerr << "Tipe node tidak dapat di dengar." << std::endl;
        break;
  }
}

// Function
auto parser::nodeTypeToString(const NodeType &type) -> std::string {
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

void parser::coutNode(const Node &root, int initialSpace) { // NOLINT(misc-no-recursion)
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

auto parser::ParseNode::error(
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

auto parser::ParseNode::peek() const -> const lexer::Token & {
  return this->tokens[this->current];
}

auto parser::ParseNode::isAtEnd() const -> bool {
  return this->peek().type == lexer::TokenType::akhirDariFile;
}

auto parser::ParseNode::check(const lexer::TokenType &type) const -> bool {
  if (this->isAtEnd()) {
    return false;
  }
  return this->peek().type == type;
}

auto parser::ParseNode::previous() -> const lexer::Token & {
  if (this->current == 0) {
    throw std::out_of_range("Berusaha mengakses token sebelum indeks awal.");
  }
  return this->tokens[this->current - 1];
}

auto parser::ParseNode::advance() -> const lexer::Token & {
  if (!this->isAtEnd()) {
    this->current++;
  }
  return this->previous();
}

auto parser::ParseNode::consume(
  const lexer::TokenType &type,
  const std::string &errorMessage
) -> const lexer::Token & {
  if (this->check(type)) {
    return this->advance();
  }
  throw parser::ParseNode::error(this->peek(), errorMessage);
}

auto parser::ParseNode::match(const std::vector<lexer::TokenType> &types) -> bool {
  if(std::ranges::any_of(
    types,
    [this](auto type) { return this->check(type); }
    )) {
    this->advance();
    return true;
  }
  return false;
}

auto parser::ParseNode::parse() -> std::unique_ptr<parser::Node> {
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
auto parser::ParseNode::parsePernyataanEkspresi() -> std::unique_ptr<parser::Node> { // NOLINT(misc-no-recursion)
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
    throw parser::ParseNode::error(this->peek(), "Pernyataan ekspresi tidak benar.");
  }

  return std::make_unique<Node>(std::move(node));
}

// * Parse Fungsi Group
auto parser::ParseNode::parsePanggilFungsi() -> std::unique_ptr<parser::Node> { // NOLINT(misc-no-recursion)
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

auto parser::ParseNode::parseTempatParameterPanggilFungsi() -> std::unique_ptr<parser::Node> {
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