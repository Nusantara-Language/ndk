#pragma once

#include "node/node.hpp"

namespace nusantara {

  // Class
  class SemanticAnalyzer: public INodeVisitor<bool> {
    public:
    private:
      // Fungsi
      auto visitTokenNode(const Node &node) -> bool override;
      auto visitPanggilFungsiNode(const Node &node) -> bool override;
      auto visitAwalNode(const Node &node) -> bool override;
      auto visitTempatParameterPanggilFungsiNode(const Node &node) -> bool override;
      auto visitPernyataanEkspresiNode(const Node &node) -> bool override;
  };

} // namespace nusantara