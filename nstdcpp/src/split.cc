#include "split.h"
#include <sstream>

std::vector<std::string> nstd::split(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string token;
    std::stringstream ss(str);
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    return result;
}