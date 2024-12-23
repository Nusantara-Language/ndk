#pragma once

#include <cstddef>
#include <functional>
#include <regex>
#include <string>
#include <vector>

namespace nusantara {

  class CommandExecutor;

  class Command {
    public:
      Command(
        std::string name,
        std::string description,
        std::function<void(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args)> func,
        const bool &noArgs
      );

      Command(
        std::regex regex,
        std::string name,
        std::string description,
        std::function<void(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args)> func,
        const bool &noArgs
      );

      [[nodiscard]] auto getName() const -> const std::string&;

      [[nodiscard]] auto getDesc() const -> const std::string&;

      [[nodiscard]] auto getRegex() const -> const std::regex&;

      [[nodiscard]] auto toString() const -> std::string;

      auto execute(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args) -> void;

      auto operator==(const Command& other) -> bool;

    private:
      bool noArgs;
      std::function<void(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args)> func;
      std::string name;
      std::string description;
      std::regex regex;
  };

  class CommandExecutor {
    public:
      CommandExecutor() = default;

      auto add(Command arg) -> void;

      auto getCommands() -> const std::vector<Command>&;

      auto execute(std::vector<std::string> args) -> void;

    private:
      std::vector<Command> commands;
  };

} // namespace nusantara