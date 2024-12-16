#include "parser.h"
#include "lexer.h"
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

std::string Parser::nodeTypeToString(const NodeType &type) {
  switch (type) {
  case AWAL:
    return "AWAL";
  case PERNYATAAN:
    return "PERNYATAAN";
  case DEKLARASI_FUNGSI:
    return "DEKLARASI FUNGSI";
  case PARAMETER_DEKLARASI_FUNGSI:
    return "PARAMETER DEKLARASI FUNGSI";
  case TOKEN:
    return "TOKEN";
  case BLOK_KODE:
    return "BLOK KODE";
  default:
    std::cerr << "Invalid Node type!" << std::endl;
    exit(1);
    break;
  }
}

void Parser::Node::addChild(std::unique_ptr<Node> node) {
  this->children.push_back(std::move(node));
}

void Parser::coutNode(const Node &node, int space) {
  if (node.type != NodeType::TOKEN) {
    std::cout << "\033[34m[" << nodeTypeToString(node.type) << "]\033[0m\n";
  }

  if (node.token) {
    std::cout << Lexer::tokenTypeToString(node.token->type) << ": \033[33m"
              << node.token->content << "\033[0m\n";
  }

  space += 3;

  for (const auto &child : node.children) {
    std::cout << std::string(space, ' ') << "\033[32m|\033[0m\n";
    std::cout << std::string(space, ' ') << "\033[32m->\033[0m";
    coutNode(*child, space);
  }
}

void Parser::ParseErrorManager::addError(const Lexer::Token& token, const std::string& message)
{
  
}

std::string Parser::ParseNode::error(
  const Lexer::Token &token,
  const std::string &message
) {
  throw ParserException(
    std::format(
      "Kesalahan sintaks pada {}:{}:{}\n -> {}", 
      token.fileName, 
      token.row,
      token.column,
      message
    )
  );
}

const Lexer::Token &Parser::ParseNode::peek() const {
  return this->tokens[this->current];
}

const bool Parser::ParseNode::isAtEnd() const {
  return this->peek().type == Lexer::TokenType::AKHIR_DARI_FILE;
}

const bool Parser::ParseNode::check(const Lexer::TokenType &type) {
  if (this->isAtEnd())
    return false;
  return this->peek().type == type;
}

const Lexer::Token &Parser::ParseNode::previous() {
  if (this->current == 0) {
    throw std::out_of_range(
        "Attempted to access token before the start of the token stream.");
  }
  return this->tokens[this->current - 1];
}

const Lexer::Token &Parser::ParseNode::advance() {
  if (!this->isAtEnd()) {
    this->current++;
  }
  return this->previous();
}

const Lexer::Token &
Parser::ParseNode::consume(const Lexer::TokenType &type,
                           const std::string &errorMessage) {
  if (this->check(type))
    return this->advance();
  throw this->error(this->peek(), errorMessage);
}

const bool
Parser::ParseNode::match(const std::vector<Lexer::TokenType> &types) {
  for (Lexer::TokenType type : types) {
    if (this->check(type)) {
      this->advance();
      return true;
    }
  }
  return false;
}

std::unique_ptr<Parser::Node> Parser::ParseNode::parse()
{
    auto node = Node{NodeType::AWAL};
    while (!this->isAtEnd()) {
        try {
          node.addChild(this->parsePernyataan());
        } catch (const ParserException& error) {
          this->advance();
          std::cerr << error.what() << "\n\n";
        }
    }
    return std::make_unique<Node>(std::move(node));
}

// * Parse Core
std::unique_ptr<Parser::Node> Parser::ParseNode::parsePernyataan() 
{
    auto node = Node{NodeType::PERNYATAAN};

    if(this->check(Lexer::TokenType::FUNGSI))
    {
      node.addChild(this->parseDeklarasiFungsi());
    }else{
      throw this->error(this->peek(), "Pernyataan ini tidak benar.");
    }

    return std::make_unique<Node>(std::move(node));
}

// * Parse Fungsi Group
std::unique_ptr<Parser::Node> Parser::ParseNode::parseDeklarasiFungsi() 
{
    auto node = Node{NodeType::DEKLARASI_FUNGSI};
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::FUNGSI, 
                    "Untuk membuat fungsi harus menggunakan kata kunci 'fungsi' di awal."
                )
            }
        )
    );
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::IDENTIFIKASI, 
                    "Nama fungsi belum ditentukan."
                )
            }
        )
    );
    node.addChild(this->parseParameterDeklarasiFungsi());
    node.addChild(this->parseBlokKode());
    return std::make_unique<Node>(std::move(node));
}

std::unique_ptr<Parser::Node> Parser::ParseNode::parseParameterDeklarasiFungsi() 
{
    auto node = Node{NodeType::PARAMETER_DEKLARASI_FUNGSI};
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::KURUNG_BULAT_BUKA, 
                    "Parameter harus di awali dengan kurung buka '('."
                )
            }
        )
    );
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::KURUNG_BULAT_TUTUP, 
                    "Parameter harus di akhiri dengan kurung tutup ')'."
                )
            }
        )
    );
    return std::make_unique<Node>(std::move(node));
}

// * Parse Blok Kode
std::unique_ptr<Parser::Node> Parser::ParseNode::parseBlokKode() 
{
    auto node = Node{NodeType::BLOK_KODE};
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::KURUNG_KURAWAL_BUKA, 
                    "Blok kode harus di awali dengan kurung kurawal buka '{'."
                )
            }
        )
    );
    while(!check(Lexer::TokenType::KURUNG_KURAWAL_TUTUP)) {
        node.addChild(this->parsePernyataan());
    }
    node.addChild(
        std::make_unique<Node>(
            Node{
                NodeType::TOKEN,
                this->consume(
                    Lexer::TokenType::KURUNG_KURAWAL_TUTUP, 
                    "Blok kode harus diakhiri dengan kurung kurawal tutup '}'."
                )
            }
        )
    );
    return std::make_unique<Node>(std::move(node));
}