#pragma once

#include <cstdint>

namespace nstd {

enum SleepType { seconds, milliSeconds, microSeconds };

void sleep(const SleepType &type, const int64_t &time);

} // namespace nstd