#pragma once

namespace nusantara {

  class Node;

  class INodeListener {
    public:
      // Constructor
      INodeListener() = default;
      INodeListener(const INodeListener &) = default;
      INodeListener(INodeListener &&) = default;
      auto operator=(const INodeListener &) -> INodeListener & = default;
      auto operator=(INodeListener &&) -> INodeListener & = default;
      virtual ~INodeListener() = default;

      // Fungsi
      virtual auto enterAWAL(const nusantara::Node &node) -> void = 0;
      virtual auto exitAWAL(const nusantara::Node &node) -> void = 0;

      virtual auto enterPernyataanEkspresi(const nusantara::Node &node) -> void = 0;
      virtual auto exitPernyataanEkspresi(const nusantara::Node &node) -> void = 0;

      virtual auto enterPanggilFungsi(const nusantara::Node &node) -> void = 0;
      virtual auto exitPanggilFungsi(const nusantara::Node &node) -> void = 0;

      virtual auto enterTempatParameterPanggilFungsi(const nusantara::Node &node) -> void = 0;
      virtual auto exitTempatParameterPanggilFungsi(const nusantara::Node &node) -> void = 0;

      virtual auto enterToken(const nusantara::Node &node) -> void = 0;
      virtual auto exitToken(const nusantara::Node &node) -> void = 0;
  };


} // namespace nusantara