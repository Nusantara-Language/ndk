#pragma once

#include <string>
#include <vector>

namespace nstd {

auto split(const std::string &str, char delimiter) -> std::vector<std::string>;

} // namespace nstd