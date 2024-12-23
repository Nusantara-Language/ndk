#pragma once

#include "node/node.hpp"
#include "visitor/visitor.hpp"
#include "runtime/runtime.hpp"

namespace nusantara {

  class Interpreter: public INodeVisitor<void> {
    public:

    private:
      Runtime runtime;

      void visitAwalNode(const Node &node) override;
      void visitPanggilFungsiNode(const Node &node) override;
      void visitTempatParameterPanggilFungsiNode(const Node &node) override;
      void visitPernyataanEkspresiNode(const Node &node) override;
      void visitTokenNode(const Node &node) override;
  };

}