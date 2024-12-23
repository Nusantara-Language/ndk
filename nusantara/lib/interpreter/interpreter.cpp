// Include STD C++
#include <iostream>
#include <memory>
#include <string>

// Include project file
#include "interpreter/interpreter.hpp"
#include "cetak/cetak.hpp"
#include "parser/parser.hpp"
#include "semantic_analyzer/semantic_analyzer.hpp"

// Interpreter Class
auto nusantara::Interpreter::interpretation(const std::unique_ptr<nusantara::Node> &node) -> void { // NOLINT(misc-no-recursion)
  if (!nusantara::SemanticAnalyzer::analyze(*node)) {
    std::cerr << "Analisis semantik gagal. Eksekusi dihentikan." << std::endl;
    return;
  }
  
  if (node) {
    switch (node->getType()) {
      case nusantara::NodeType::PANGGIL_FUNGSI:
        interpretFunctionCall(*node);
        break;
      case nusantara::AWAL:
        interpretAwal(*node);
        break;
      case nusantara::PERNYATAAN_EKSPRESI:
        interpretPernyataanEkspresi(*node);
        break;
      case nusantara::TOKEN:
        interpretToken(*node);
        break;
      case nusantara::TEMPAT_PARAMETER_PANGGIL_FUNGSI:
        interpretTempatParameterPanggilFungsi(*node);
        break;
      default:
        std::cerr << "Terjadi kesalahan: Tipe node tidak dapat di eksekusi interpreter." << "\n";
        break;
    }
  }
}

auto nusantara::Interpreter::interpretToken(const nusantara::Node& node) -> std::string {
  return node.getToken()->content;
}

auto nusantara::Interpreter::interpretFunctionCall(const nusantara::Node& node) -> void {
  const std::string &functionName = interpretToken(*node.getChildren()[0]);

  if(functionName == "halodunia") {
    nstd::cetakDBB("Halo Dunia!");
  } else {
    std::cerr << "Fungsi '" << functionName << "' tidak dikenali." << "\n";
  }
}

auto nusantara::Interpreter::interpretAwal(const nusantara::Node& node) -> void {  // NOLINT(misc-no-recursion)
  for (const auto& child : node.getChildren()) {
    interpretation(child);
  }
}

auto nusantara::Interpreter::interpretPernyataanEkspresi(const nusantara::Node& node) -> void {  // NOLINT(misc-no-recursion)
  for (const auto& child : node.getChildren()) {
    interpretation(child);
  }
}

auto nusantara::Interpreter::interpretTempatParameterPanggilFungsi(const nusantara::Node&  /*node*/) -> void {
  // Tidak mengeksekusi apa apa
}
