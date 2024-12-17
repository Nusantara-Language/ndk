// Header guard
#ifndef LISTENER_HPP
#define LISTENER_HPP

namespace parser {

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
      virtual auto enterAWAL(const parser::Node &node) -> void = 0;
      virtual auto exitAWAL(const parser::Node &node) -> void = 0;

      virtual auto enterPernyataanEkspresi(const parser::Node &node) -> void = 0;
      virtual auto exitPernyataanEkspresi(const parser::Node &node) -> void = 0;

      virtual auto enterPanggilFungsi(const parser::Node &node) -> void = 0;
      virtual auto exitPanggilFungsi(const parser::Node &node) -> void = 0;

      virtual auto enterTempatParameterPanggilFungsi(const parser::Node &node) -> void = 0;
      virtual auto exitTempatParameterPanggilFungsi(const parser::Node &node) -> void = 0;

      virtual auto enterToken(const parser::Node &node) -> void = 0;
      virtual auto exitToken(const parser::Node &node) -> void = 0;
  };


} // namespace parser

#endif