#include "interpreter/interpreter.hpp"
#include <any>
#include <string>

auto nusantara::Interpreter::visitTokenNode(const nusantara::Node& node) -> void {
  // Atur data sementara di runtime untuk menyimpan nama fungsi.
  if(node.getToken()) this->runtime.aturDataSementara(node.getToken()->content);
}

auto nusantara::Interpreter::visitPanggilFungsiNode(const nusantara::Node& node) -> void {
  // Pergi ke child index ke-0 untuk mendapatkan nama fungsi
  node.getChildren()[0]->accept(*this);

  // Panggil fungsi sesuai nama
  this->runtime.ambilKawasan()
    .ambilKumpulanFungsi()
    .panggilFungsi(
      std::any_cast<std::string>(
        this->runtime.ambilDataSementara()
      )
    );
}

auto nusantara::Interpreter::visitAwalNode(const nusantara::Node& node) -> void {  // NOLINT(misc-no-recursion)
  for (const auto& child : node.getChildren()) {
    child->accept(*this);
  }
}

auto nusantara::Interpreter::visitPernyataanEkspresiNode(const nusantara::Node& node) -> void {  // NOLINT(misc-no-recursion)
  if(node.getChildren().size() > 0) node.getChildren()[0]->accept(*this);
}

auto nusantara::Interpreter::visitTempatParameterPanggilFungsiNode(const nusantara::Node&  /*node*/) -> void {
  // Tidak mengeksekusi apa apa
}
