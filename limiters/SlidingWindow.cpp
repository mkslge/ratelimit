//
// Created by Mark on 3/24/26.
//

#include "SlidingWindow.h"


bool SlidingWindow::make_request(ID id) {
    return SlidingWindow::make_request(id, 1.0);
}

bool SlidingWindow::make_request(ID id, double cost) {
    if (!clients.contains(id) ) {
        clients[id] = std::make_unique<SlidingWindowClient>(id);
    }

    auto* client = dynamic_cast<SlidingWindowClient*>(clients[id].get());
    std::deque<Request>& window = client->get_window();

    //while client info dequeue old requests not in window, remove them, decrement cost
    double curr_timestamp = timeUtil::curr_time();
    while (!window.empty() && window.front().time < curr_timestamp - static_cast<long long>(window_length_)) {
        Request to_remove = window.front();
        window.pop_front();
        client->sub_window_sum(to_remove.cost);
    }

    //then check if we have space to current request to our window
    if (cost > rate_per_second_ || cost + client->get_window_sum() > (rate_per_second_ * window_length_)) {
        return false;
    }

    Request new_request{timeUtil::curr_time(), cost};
    window.push_back(new_request);
    client->add_window_sum(cost);

    return true;
}


