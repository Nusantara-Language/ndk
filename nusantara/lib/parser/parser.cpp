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
#include "visitor/visitor.hpp"
#include "lexer/lexer.hpp"
#include "listener/listener.hpp"
#include "parser/parser.hpp"

// Class Node
nusantara::Node::Node(const Node& other): type(other.type), token(other.token) {
  for(const auto& child : other.children) {
    children.push_back(std::make_unique<Node>(*child));
  }
}

auto nusantara::Node::getType() const -> const NodeType & { return this->type; }

auto nusantara::Node::getToken() const -> const std::optional<nusantara::Token> & {
  return this->token;
}

auto nusantara::Node::getChildren() const -> const std::vector<std::unique_ptr<Node>> & {
  return this->children;
}

void nusantara::Node::addChild(std::unique_ptr<Node> node) {
  this->children.push_back(std::move(node));
}

auto nusantara::Node::operator<(const Node& other) const -> bool {
  bool tokenBoolTemp = false;
  if(this->token && other.token) {
    tokenBoolTemp = this->token->type < other.token->type;
  }
  return this->type < other.type && tokenBoolTemp && (this->children.size() < other.children.size());
}

void nusantara::Node::accept(INodeListener& listener) const { // NOLINT(misc-no-recursion)
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
auto nusantara::nodeTypeToString(const NodeType &type) -> std::string {
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

void nusantara::printNode(const Node &root, int initialSpace) { // NOLINT(misc-no-recursion)
  if (root.getType() != NodeType::TOKEN) {
    std::cout << "\033[34m[" << nodeTypeToString(root.getType()) << "]\033[0m\n";
  }

  if (root.getToken()) {
    std::cout << nusantara::tokenTypeToString(root.getToken()->type) 
    << ": \033[33m" << root.getToken()->content << "\033[0m\n";
  }

  initialSpace += 3;

  for (const auto &child : root.getChildren()) {
    std::cout << std::string(initialSpace, ' ') << "\033[32m|\033[0m\n";
    std::cout << std::string(initialSpace, ' ') << "\033[32m->\033[0m";
    printNode(*child, initialSpace);
  }
}

auto nusantara::Parser::error(
  const nusantara::Token &token,
  const std::string &message
) -> ParserException {
  return ParserException(
    std::format(
    "Kesalahan sintaks pada {}:{}:{}\n -> {}",
      token.filePath, 
      token.location.row,
      token.location.column, 
      message
    )
  );
}

auto nusantara::Parser::peek() const -> const nusantara::Token & {
  return this->tokens[this->current];
}

auto nusantara::Parser::isAtEnd() const -> bool {
  return this->peek().type == nusantara::TokenType::akhirDariFile;
}

auto nusantara::Parser::check(const nusantara::TokenType &type) const -> bool {
  if (this->isAtEnd()) {
    return false;
  }
  return this->peek().type == type;
}

auto nusantara::Parser::previous() -> const nusantara::Token & {
  if (this->current == 0) {
    throw std::out_of_range("Berusaha mengakses token sebelum indeks awal.");
  }
  return this->tokens[this->current - 1];
}

auto nusantara::Parser::advance() -> const nusantara::Token & {
  if (!this->isAtEnd()) {
    this->current++;
  }
  return this->previous();
}

auto nusantara::Parser::consume(
  const nusantara::TokenType &type,
  const std::string &errorMessage
) -> const nusantara::Token & {
  if (this->check(type)) {
    return this->advance();
  }
  throw nusantara::Parser::error(this->peek(), errorMessage);
}

auto nusantara::Parser::match(const std::vector<nusantara::TokenType> &types) -> bool {
  if(std::ranges::any_of(
    types,
    [this](auto type) { return this->check(type); }
    )) {
    this->advance();
    return true;
  }
  return false;
}

auto nusantara::Parser::parsing() -> void {
  auto node = Node{NodeType::AWAL};
  while (!this->isAtEnd()) {
    try {
      node.addChild(this->parsePernyataanEkspresi());
    } catch (const ParserException &error) {
      std::cerr << error.what() << "\n\n";
      this->advance();
    }
  }
  this->parsingResult = std::make_unique<Node>(std::move(node));
}

// * Parse Core
auto nusantara::Parser::parsePernyataanEkspresi() -> std::unique_ptr<nusantara::Node> { // NOLINT(misc-no-recursion)
  auto node = Node{NodeType::PERNYATAAN_EKSPRESI};

  auto consumeTitikKoma = [this] -> const nusantara::Token & {
    return this->consume(
      nusantara::TokenType::titikKoma,
      "Jangan lupa titik koma."
    );
  };

  if(this->check(nusantara::TokenType::identifikasi)) {
    node.addChild(this->parsePanggilFungsi()); 
    if(this->ast) {
      consumeTitikKoma();
    }else{
      node.addChild(
        std::make_unique<Node>(
          Node{
            NodeType::TOKEN, 
            consumeTitikKoma()
          }
        )
      );
    }
  }else{
    throw nusantara::Parser::error(this->peek(), "Pernyataan ekspresi tidak benar.");
  }

  return std::make_unique<Node>(std::move(node));
}

// * Parse Fungsi Group
auto nusantara::Parser::parsePanggilFungsi() -> std::unique_ptr<nusantara::Node> { // NOLINT(misc-no-recursion)
  auto node = Node{NodeType::PANGGIL_FUNGSI};

  node.addChild(
    std::make_unique<Node>(
      Node{
        NodeType::TOKEN, 
        this->consume(
          nusantara::TokenType::identifikasi,
          "Nama fungsi belum ditentukan."
        )
      }
    )
  );

  node.addChild(this->parseTempatParameterPanggilFungsi());

  return std::make_unique<Node>(std::move(node));
}

auto nusantara::Parser::parseTempatParameterPanggilFungsi() -> std::unique_ptr<nusantara::Node> {
  auto node = Node{NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI};

  auto consumeKurungBulatBuka = [this] -> const nusantara::Token& {
    return this->consume(
      nusantara::TokenType::kurungBulatBuka,
      "Tempat parameter pada fungsi harus ada kurung bulat buka '('."
    );
  };

  auto consumeKurungBulatTutup = [this] -> const nusantara::Token& {
    return this->consume(
      nusantara::TokenType::kurungBulatTutup,
      "Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
    );
  };

  if(this->ast) {
    consumeKurungBulatBuka();
    consumeKurungBulatTutup();
  }else{
    node.addChild(
      std::make_unique<Node>(
        Node{
          NodeType::TOKEN,
          consumeKurungBulatBuka()
        }
      )
    );

    node.addChild(
      std::make_unique<Node>(
        Node{
          NodeType::TOKEN,
          consumeKurungBulatTutup()
        }
      )
    );
  }

  return std::make_unique<Node>(std::move(node));
}

auto nusantara::Parser::print() -> void {
  if(this->parsingResult != nullptr) {
    printNode(*this->parsingResult, 0);
  }
}

auto nusantara::Parser::getResult() const -> const std::unique_ptr<Node>& {
  return this->parsingResult;
}

auto nusantara::Parser::setTokens(const std::vector<nusantara::Token>& tokens) -> void {
  this->tokens = tokens;
}