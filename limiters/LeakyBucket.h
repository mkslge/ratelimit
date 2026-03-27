//
// Created by Mark on 3/25/26.
//

#ifndef LEAKYBUCKET_H
#define LEAKYBUCKET_H
#include "FixedWindow.h"
#include "RateLimiter.h"
#include <queue>
#include <thread>

using Request = int;

class LeakyBucket : public RateLimiter {
private:
    std::queue<Request> msg_queue_;
    std::mutex mut_;
    bool shutdown_;
    int ms_rate_;
    std::thread request_thread_;
    std::condition_variable cv_;
public:
    explicit LeakyBucket(double rate_per_second, int ms_rate) : RateLimiter(rate_per_second), shutdown_(false), ms_rate_(ms_rate) {

        request_thread_ = std::thread{&LeakyBucket::msg_queue_thread, this};
    }
    bool make_request(ID id) override;
    bool make_request(ID id, double cost) override;



    void shutdown_bucket();

    ~LeakyBucket() override {
        if (request_thread_.joinable()) {
            request_thread_.join();
        }
    }

private:
    void msg_queue_thread();
};



#endif //LEAKYBUCKET_H
