//
// Created by Mark on 3/26/26.
//

#ifndef SLIDINGWINDOWCLIENT_H
#define SLIDINGWINDOWCLIENT_H

#include <deque>
#include <chrono>
#include "Client.h"

struct Request {
    double time;
    double cost;
};

//request maps time and cost of request


class SlidingWindowClient : public Client {
private:
    double window_sum_;
    std::deque<Request> window_;
public:
    explicit SlidingWindowClient(int id) : Client(id), window_sum_(0) {}

    double get_window_sum() const {
        return window_sum_;
    }

    std::deque<Request>& get_window() {
        return window_;
    }

    void sub_window_sum(double to_sub) {
        window_sum_ -= to_sub;
    }

    void add_window_sum(double to_add) {
        window_sum_ += to_add;
    }




};



#endif //SLIDINGWINDOWCLIENT_H
