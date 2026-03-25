//
// Created by Mark on 3/24/26.
//

#ifndef FIXEDWINDOW_H
#define FIXEDWINDOW_H
#include "RateLimiter.h"
#include "../ClientInfo.h"
#include <chrono>
#include <cmath>



class FixedWindow : public RateLimiter {
private:
    double window_length_;

public:
    FixedWindow(double rate_per_sec, double window) : RateLimiter(rate_per_sec), window_length_(window) {};
    bool make_request(ID id) override;
    bool make_request(ID id, double cost) override;
    ~FixedWindow() override = default;


private:
    long double gen_window() const;
};



#endif //FIXEDWINDOW_H
