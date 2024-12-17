// Header guard
#ifndef SPLIT_HPP
#define SPLIT_HPP

// Include STD C++
#include <string>
#include <vector>

// Namespace
namespace nstd {

  // Function
  auto split(const std::string &str, char delimiter) -> std::vector<std::string>;

} // namespace nstd

#endif
