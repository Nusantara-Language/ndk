#pragma once

namespace sleep {

    enum type {
        SECONDS,
        MILLISECONDS,
        MICROSECONDS
    };

    void start(const type &type, const long long &time);

}