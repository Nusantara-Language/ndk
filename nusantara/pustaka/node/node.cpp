#include "node/node.hpp"

// Class Node
nusantara::Node::Node(const Node& other): type(other.type), token(other.token) {
  for(const auto& child : other.children) {
    children.push_back(std::make_unique<Node>(*child));
  }
}

auto nusantara::Node::getType() const -> const NodeType & { return this->type; }

auto nusantara::Node::getToken() const -> const std::optional<nusantara::Token> & {
  return this->token;
}

auto nusantara::Node::getChildren() const -> const std::vector<std::unique_ptr<Node>> & {
  return this->children;
}

void nusantara::Node::addChild(std::unique_ptr<Node> node) {
  this->children.push_back(std::move(node));
}

auto nusantara::Node::operator<(const Node& other) const -> bool {
  bool tokenBoolTemp = false;
  if(this->token && other.token) {
    tokenBoolTemp = this->token->type < other.token->type;
  }
  return this->type < other.type && tokenBoolTemp && (this->children.size() < other.children.size());
}

void nusantara::Node::accept(INodeListener& listener) const { // NOLINT(misc-no-recursion)
  switch (this->type) {
    case NodeType::AWAL:
        listener.enterAWAL(*this);
        break;
    case NodeType::PERNYATAAN_EKSPRESI:
        listener.enterPernyataanEkspresi(*this);
        break;
    case NodeType::PANGGIL_FUNGSI:
        listener.enterPanggilFungsi(*this);
        break;
    case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
        listener.enterTempatParameterPanggilFungsi(*this);
        break;
    case NodeType::TOKEN:
        listener.enterToken(*this);
        break;
    default:
        std::cerr << "Tipe node tidak dapat di dengar." << std::endl;
        break;
  }

  for(const auto& child : children) {
      child->accept(listener);
  }

  switch (this->type) {
    case NodeType::AWAL:
        listener.exitAWAL(*this);
        break;
    case NodeType::PERNYATAAN_EKSPRESI:
        listener.exitPernyataanEkspresi(*this);
        break;
    case NodeType::PANGGIL_FUNGSI:
        listener.exitPanggilFungsi(*this);
        break;
    case NodeType::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
        listener.exitTempatParameterPanggilFungsi(*this);
        break;
    case NodeType::TOKEN:
        listener.exitToken(*this);
        break;
    default:
        std::cerr << "Tipe node tidak dapat di dengar." << std::endl;
        break;
  }
}

void nusantara::printNode(const Node &root, int initialSpace) { // NOLINT(misc-no-recursion)
  if (root.getType() != NodeType::TOKEN) {
    std::cout << "\033[34m[" << nodeTypeToString(root.getType()) << "]\033[0m\n";
  }

  if (root.getToken()) {
    std::cout << nusantara::tokenTypeToString(root.getToken()->type) 
    << ": \033[33m" << root.getToken()->content << "\033[0m\n";
  }

  initialSpace += 3;

  for (const auto &child : root.getChildren()) {
    std::cout << std::string(initialSpace, ' ') << "\033[32m|\033[0m\n";
    std::cout << std::string(initialSpace, ' ') << "\033[32m->\033[0m";
    printNode(*child, initialSpace);
  }

}