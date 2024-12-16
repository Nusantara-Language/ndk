#pragma once

namespace nstd {

    enum SleepType {
        SECONDS,
        MILLISECONDS,
        MICROSECONDS
    };

    void sleep(const SleepType &type, const long long &time);

}