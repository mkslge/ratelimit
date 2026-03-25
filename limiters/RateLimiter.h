//
// Created by Mark on 3/24/26.
//

#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <unordered_map>
#include <memory>
#include "../ClientInfo.h"


using ID = int;

class RateLimiter {
protected:
    double rate_per_second_{};
    std::unordered_map<ID, std::unique_ptr<ClientInfo>> clients;

public:
    RateLimiter() = default;
    explicit RateLimiter(double rate_per_second) : rate_per_second_(rate_per_second) {};
    virtual bool make_request(ID id, double cost) = 0;
    virtual bool make_request(ID id) = 0;
    virtual ~RateLimiter() = default;


};



#endif //RATELIMITER_H
