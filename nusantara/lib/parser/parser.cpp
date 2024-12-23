// Include STD C++
#include <algorithm>
#include <cstdlib>
#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "visitor/visitor.hpp"

#include "listener/listener.hpp"

#include "parser/parser.hpp"

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
    throw std::out_of_range("[P] Berusaha mengakses token sebelum indeks awal.");
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
      "[P] Jangan lupa titik koma."
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
          "[P] Nama fungsi belum ditentukan."
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
      "[P] Tempat parameter pada fungsi harus ada kurung bulat buka '('."
    );
  };

  auto consumeKurungBulatTutup = [this] -> const nusantara::Token& {
    return this->consume(
      nusantara::TokenType::kurungBulatTutup,
      "[P] Tempat parameter pada fungsi harus di akhiri dengan kurung tutup ')'."
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