// Header guard
#ifndef TEST_VISITOR_HPP
#define TEST_VISITOR_HPP

#include "visitor.hpp"
#include "parser.hpp"
#include <iostream>

class TestVisitor: public parser::INodeVisitor<void> {
  public:
    void visitAwalNode(const parser::Node &node) override {
      std::cout << "[Visitor]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void visitPernyataanEkspresiNode(const parser::Node &node) override {
      std::cout << "[Visitor]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void visitPanggilFungsiNode(const parser::Node &node) override {
      std::cout << "[Visitor]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void visitTempatParameterPanggilFungsiNode(const parser::Node &node) override {
      std::cout << "[Visitor]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void visitTokenNode(const parser::Node &node) override {
      std::cout << "[Visitor]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }
};

#endif