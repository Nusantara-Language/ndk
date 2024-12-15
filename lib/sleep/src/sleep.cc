#include "sleep.h"
#include <chrono>
#include <iostream>
#include <thread>

void sleep::start(const type &type, const long long &time)
{
    switch (type) {
    case SECONDS:
        std::this_thread::sleep_for(std::chrono::seconds(time));
        break;
    case MILLISECONDS:
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
        break;
    case MICROSECONDS:
        std::this_thread::sleep_for(std::chrono::microseconds(time));
        break;
    default:
        std::cerr << "Invalid time type!" << std::endl;
        break;
    }
}