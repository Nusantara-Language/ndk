#pragma once

#include "visitor/visitor.hpp"

namespace nusantara {
  class IRVisitor: INodeVisitor<void> {
    void visitAwalNode(const Node &node) override;
    void visitPernyataanEkspresiNode(const Node &node) override;
    void visitPanggilFungsiNode(const Node &node) override;
    void visitTempatParameterPanggilFungsiNode(const Node &node) override;
    void visitTokenNode(const Node &node) override;
  };
} // namespace nusantara