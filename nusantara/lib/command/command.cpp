#include <algorithm>
#include <cstddef>
#include <format>
#include <functional>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include "command/command.hpp"
#include "cetak/cetak.hpp"


nusantara::Command::Command(
  std::string name,
  std::string description,
  std::function<void(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args)> func,
  const bool &noArgs
): Command(
  std::regex(name),
  std::move(name),
  std::move(description),
  std::move(func),
  noArgs
) {}

nusantara::Command::Command(
  std::regex regex,
  std::string name,
  std::string description,
  std::function<void(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args)> func,
  const bool &noArgs
):
regex(std::move(regex)),
name(std::move(name)),
description(std::move(description)),
func(std::move(func)),
noArgs(noArgs)
{}

auto nusantara::Command::getName() const -> const std::string& {
  return this->name;
}

auto nusantara::Command::getDesc() const -> const std::string& {
  return this->description;
}

auto nusantara::Command::getRegex() const -> const std::regex& {
  return this->regex;
}

auto nusantara::Command::toString() const -> std::string {
  return std::format(
    "{} - {}",
    this->name,
    this->description
  );
}

auto nusantara::Command::execute(CommandExecutor &cExec, size_t &currentIndex, std::vector<std::string> &args) -> void {
  if(this->noArgs && args.size() > 2) {
    nstd::cetakDF("Perintah {} tidak memerlukan argumen.", this->name);
    return;
  }
  this->func(cExec, currentIndex, args);
}

auto nusantara::Command::operator==(const Command& other) -> bool {
  return this->name == other.name || this->description == other.description;
}

auto nusantara::CommandExecutor::add(Command arg) -> void {
  if(std::find(this->commands.begin(), this->commands.end(), arg) == this->commands.end()) {
    this->commands.push_back(std::move(arg));
  }
}

auto nusantara::CommandExecutor::getCommands() -> const std::vector<Command>& {
  return this->commands;
}

auto nusantara::CommandExecutor::execute(std::vector<std::string> args) -> void {
  size_t currentIndex = 1;

  if(args.size() == 1) {
    this->commands[0].execute(*this, currentIndex, args);
    return;
  }
  
  for(auto& arg: this->commands) {
    if(std::regex_match(args[currentIndex], arg.getRegex())) {
      arg.execute(*this, currentIndex, args);
      currentIndex++;
      return;
    }
  }

  nstd::cetakDF("Perintah '{}' tidak ada.", args[currentIndex]);
}