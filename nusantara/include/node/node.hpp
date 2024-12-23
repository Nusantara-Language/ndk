#pragma once

#include "listener/listener.hpp"
#include "node/node_type.hpp"
#include "token/token.hpp"
#include "visitor/visitor.hpp"
#include <iostream>
#include <optional>
#include <vector>

namespace nusantara {

  void printNode(const Node &root, int initialSpace);

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
      auto accept(INodeVisitor<T>& visitor) const -> T {
        switch (this->type) {
          case NodeType::AWAL:
              return visitor.visitAwalNode(*this);
          case NodeType::PERNYATAAN_EKSPRESI:
              return visitor.visitPernyataanEkspresiNode(*this);
          case NodeType::PANGGIL_FUNGSI:
              return visitor.visitPanggilFungsiNode(*this);
          case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
              return visitor.visitTempatParameterPanggilFungsiNode(*this);
          case NodeType::TOKEN:
              return visitor.visitTokenNode(*this);
          default:
              std::cerr << "Tipe node tidak dapat di kunjungi." << std::endl;
              break;
        }
      }

      void accept(INodeListener& listener) const;

      void addChild(std::unique_ptr<Node> node);

    private:
      NodeType type;
      std::optional<nusantara::Token> token;
      std::vector<std::unique_ptr<Node>> children;
  };

}  // namespace nusantara