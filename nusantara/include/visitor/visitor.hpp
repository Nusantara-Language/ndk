#pragma once

namespace nusantara {

  class Node;

  template<typename T>
  class INodeVisitor {
    public:
      INodeVisitor<T>() = default;
      INodeVisitor(const INodeVisitor &) = default;
      INodeVisitor(INodeVisitor &&) = default;
      auto operator=(const INodeVisitor &) -> INodeVisitor & = default;
      auto operator=(INodeVisitor &&) -> INodeVisitor & = default;
      virtual ~INodeVisitor() = default;

      // Fungsi visit
      virtual auto visitAwalNode(const Node& node) -> T = 0;
      virtual auto visitPernyataanEkspresiNode(const Node& node) -> T = 0;
      virtual auto visitPanggilFungsiNode(const Node& node) -> T = 0;
      virtual auto visitTempatParameterPanggilFungsiNode(const Node& node) -> T = 0;
      virtual auto visitTokenNode(const Node& node) -> T = 0;
  };

} // namespace nusantara