// Header guard
#ifndef TEST_LISTENER_HPP
#define TEST_LISTENER_HPP

#include "listener.hpp"
#include "parser.hpp"
#include <iostream>

class TestListener: public parser::INodeListener {
  public:
    void enterAWAL(const parser::Node &node) override {
      std::cout << "[Listener][Enter]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void exitAWAL(const parser::Node &node) override {
      std::cout << "[Listener][Exit]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void enterPernyataanEkspresi(const parser::Node &node) override {
      std::cout << "[Listener][Enter]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void exitPernyataanEkspresi(const parser::Node &node) override {
      std::cout << "[Listener][Exit]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void enterPanggilFungsi(const parser::Node &node) override {
      std::cout << "[Listener][Enter]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void exitPanggilFungsi(const parser::Node &node) override {
      std::cout << "[Listener][Exit]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void enterTempatParameterPanggilFungsi(const parser::Node &node) override {
      std::cout << "[Listener][Enter]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void exitTempatParameterPanggilFungsi(const parser::Node &node) override {
      std::cout << "[Listener][Exit]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void enterToken(const parser::Node &node) override {
      std::cout << "[Listener][Enter]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }

    void exitToken(const parser::Node &node) override {
      std::cout << "[Listener][Exit]: " << parser::nodeTypeToString(node.getType()) << "\n";
    }
};

#endif