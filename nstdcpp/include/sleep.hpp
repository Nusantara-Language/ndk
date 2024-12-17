// Header guard
#ifndef SLEEP_HPP
#define SLEEP_HPP

// Include STD C++
#include <cstdint>

// Namespace
namespace nstd {

  // Enum
  enum SleepType { seconds, milliSeconds, microSeconds };

  // Function
  void sleep(const SleepType &type, const int64_t &time);

} // namespace nstd

#endif
