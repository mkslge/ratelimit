//
// Created by Mark on 3/26/26.
//
#pragma once
#include <chrono>

namespace timeUtil {
    inline double curr_time() {
        using Clock = std::chrono::steady_clock;
        using Seconds = std::chrono::duration<double>;

        return Seconds(Clock::now().time_since_epoch()).count();
    }
}