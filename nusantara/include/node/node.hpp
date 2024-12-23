#pragma once

#include "listener/listener.hpp"
#include "node/node_type.hpp"
#include "token/token.hpp"
#include "visitor/visitor.hpp"
#include <iostream>
#include <optional>
#include <vector>

// Namespace
namespace nusantara {

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

  void printNode(const Node &root, int initialSpace);

}  // namespace nusantara