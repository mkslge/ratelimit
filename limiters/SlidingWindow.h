//
// Created by Mark on 3/24/26.
//

#ifndef SLIDINGWINDOW_H
#define SLIDINGWINDOW_H
#include "RateLimiter.h"
#include "../clients/SlidingWindowClient.h"
#include "../utility/timeUtil.h"
#include "iostream"

class SlidingWindow : public RateLimiter {
    double window_length_{};


public:
    SlidingWindow(double rate, double window) : RateLimiter(rate), window_length_(window) {

    }

    bool make_request(ID id) override;
    bool make_request(ID id, double cost) override;

private:

};



#endif //SLIDINGWINDOW_H
