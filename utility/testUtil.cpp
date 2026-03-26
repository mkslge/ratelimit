//
// Created by Mark on 3/25/26.
//
#include <chrono>
#include <iostream>
#include <thread>

namespace testUtil {
    void sleepForMilliseconds(int milliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void sleepForSeconds(int seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    }

}