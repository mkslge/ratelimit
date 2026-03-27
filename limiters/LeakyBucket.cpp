//
// Created by Mark on 3/25/26.
//

#include "LeakyBucket.h"


bool LeakyBucket::make_request(ID id) {
    return LeakyBucket::make_request(id, 1.0);
}

bool LeakyBucket::make_request(ID id, double cost) {
    std::lock_guard lg(mut_);
    if (shutdown_) {
        return false;
    }
    msg_queue_.push(id);
    cv_.notify_one();
    return true;
}

void LeakyBucket::msg_queue_thread() {

    while (!shutdown_ || !msg_queue_.empty()) {
        std::unique_lock<std::mutex> ul{mut_};
        cv_.wait(ul, [this] {return !msg_queue_.empty();});
        //std::lock_guard lg(mut_);
        //while (!msg_queue_.empty()) {
            std::cout << "Processing ID: " << msg_queue_.front() << std::endl;
            msg_queue_.pop();
            std::this_thread::sleep_for(std::chrono::milliseconds(ms_rate_));
        //}

    }

}


void LeakyBucket::shutdown_bucket() {
    std::lock_guard lg(mut_);
    shutdown_ = true;
}


