// Include STD C++
#include "split.hpp"
#include <sstream>
#include <string>
#include <vector>

// Function
auto nstd::split(
  const std::string &str, 
  char delimiter
) -> std::vector<std::string> {
  std::vector<std::string> result;
  std::string token;
  std::stringstream sstream(str);

  while (std::getline(sstream, token, delimiter)) {
    result.push_back(token);
  }

  return result;
}