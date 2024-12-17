// Include STD C++
#include <chrono>
#include <cstdint>
#include <iostream>
#include <thread>

// Include project file header
#include "sleep.hpp"

// Function
void nstd::sleep(const SleepType &type, const int64_t &time) {
  switch(type) {
    case seconds:
      std::this_thread::sleep_for(std::chrono::seconds(time));
      break;
    case milliSeconds:
      std::this_thread::sleep_for(std::chrono::milliseconds(time));
      break;
    case microSeconds:
      std::this_thread::sleep_for(std::chrono::microseconds(time));
      break;
    default:
      std::cerr << "Tipe waktu sleep tidak dapat diubah ke string." << std::endl;
      break;
    }
}