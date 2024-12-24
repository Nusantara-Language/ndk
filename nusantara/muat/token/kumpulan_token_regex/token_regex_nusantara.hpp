#pragma once

#include "token/token_regex.hpp"
#include <set>

// Namespace
namespace nusantara 
{

  auto nusantaraTokenRegexs() -> const std::set<TokenRegex>&;

}  // namespace nusantara