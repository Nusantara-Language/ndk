#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

// Include project file
#include "semantic_analyzer/semantic_analyzer.hpp"

#include "node/node.hpp"

// Semantic Analyzer Class
auto nusantara::SemanticAnalyzer::visitTokenNode(const nusantara::Node&  /*node*/) -> bool {
  return true;
}

auto nusantara::SemanticAnalyzer::visitPanggilFungsiNode(const nusantara::Node& node) -> bool {
  if(node.getChildren().empty()) {
    std::cerr << "[SA] Kesalahan: pemanggilan fungsi tanpa nama" << std::endl;
    return false;
  }

  const std::string functionName = node.getChildren()[0]->getToken()->content;
  if (functionName != "halodunia") {
    std::cerr << "[SA] Kesalahan: fungsi '" << functionName << "' tidak dikenali." << std::endl;
    return false;
  }

  return true;
}

auto nusantara::SemanticAnalyzer::visitAwalNode(const nusantara::Node& node) -> bool {  // NOLINT(misc-no-recursion)
  return std::all_of(node.getChildren().begin(), node.getChildren().end(), [this](const std::unique_ptr<Node>& child) { return child->accept<bool>(*this); });
}

auto nusantara::SemanticAnalyzer::visitPernyataanEkspresiNode(const nusantara::Node& node) -> bool {  // NOLINT(misc-no-recursion)
  return std::all_of(node.getChildren().begin(), node.getChildren().end(), [this](const std::unique_ptr<Node>& child) { return child->accept<bool>(*this); });
}

auto nusantara::SemanticAnalyzer::visitTempatParameterPanggilFungsiNode(const nusantara::Node&  /*node*/) -> bool {
  return true;
}
