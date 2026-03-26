//
// Created by Mark on 3/24/26.
//

#ifndef FIXEDWINDOW_H
#define FIXEDWINDOW_H
#include "RateLimiter.h"
#include "../clients/FixedWindowClient.h"
#include "../clients/Client.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include "../utility/timeUtil.h"
class FixedWindow : public RateLimiter {
private:
    int window_length_;

public:
    FixedWindow(double rate_per_sec, int window) : RateLimiter(rate_per_sec), window_length_(window) {};
    bool make_request(ID id) override;
    bool make_request(ID id, double cost) override;
    ~FixedWindow() override = default;


};



#endif //FIXEDWINDOW_H
