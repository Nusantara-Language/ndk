// Include STD C++
#include <algorithm>
#include <iostream>
#include <string>

// Include project file
#include "semantic_analyzer/semantic_analyzer.hpp"
#include "parser/parser.hpp"

// Semantic Analyzer Class
auto nusantara::SemanticAnalyzer::analyze(const nusantara::Node &node) -> bool { // NOLINT(misc-no-recursion)
  switch (node.getType()) {
    case nusantara::NodeType::PANGGIL_FUNGSI:
      return analyzeFunctionCall(node);
    case nusantara::AWAL:
      return analyzeAwal(node);
    case nusantara::PERNYATAAN_EKSPRESI:
      return analyzePernyataanEkspresi(node);
    case nusantara::TOKEN:
      return analyzeToken(node);
    case nusantara::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
      return analyzeTempatParameterPanggilFungsi(node);
    default:
      return true;
  }
}

auto nusantara::SemanticAnalyzer::analyzeToken(const nusantara::Node&  /*node*/) -> bool {
  return true;
}

auto nusantara::SemanticAnalyzer::analyzeFunctionCall(const nusantara::Node& node) -> bool {
  if(node.getChildren().empty()) {
    std::cerr << "Kesalahan semantik: Pemanggilan fungsi tanpa nama!" << std::endl;
    return false;
  }

  const std::string functionName = node.getChildren()[0]->getToken()->content;
  if (functionName != "halodunia") {
    std::cerr << "Kesalahan semantik: Fungsi '" << functionName << "' tidak dikenali." << std::endl;
    return false;
  }

  return true;
}

auto nusantara::SemanticAnalyzer::analyzeAwal(const nusantara::Node& node) -> bool {  // NOLINT(misc-no-recursion)
  return std::all_of(node.getChildren().begin(), node.getChildren().end(), [](const auto& node) { return analyze(*node); });
}

auto nusantara::SemanticAnalyzer::analyzePernyataanEkspresi(const nusantara::Node& node) -> bool {  // NOLINT(misc-no-recursion)
  return std::all_of(node.getChildren().begin(), node.getChildren().end(), [](const auto& node) { return analyze(*node); });
}

auto nusantara::SemanticAnalyzer::analyzeTempatParameterPanggilFungsi(const nusantara::Node&  /*node*/) -> bool {
  return true;
}
