//
// Created by Mark on 3/24/26.
//

#include "FixedWindow.h"
#include "../clients/FixedWindowClient.h"

bool FixedWindow::make_request(ID id) {
   return FixedWindow::make_request(id, 1.0);
}


bool FixedWindow::make_request(ID id, double cost) {
    long long curr_window = timeUtil::curr_time();
    if (!clients.contains(id)
        || dynamic_cast<FixedWindowClient*>(clients[id].get())->get_curr_window() + window_length_ < curr_window) {
        //still needs to subtract cost
        clients[id] = std::make_unique<FixedWindowClient>(FixedWindowClient{id, curr_window});

    }

    double requests_sent = clients[id].get()->get_requests_sent();
    if (requests_sent + cost > rate_per_second_) {
        return false;
    } else {
        clients[id].get()->add_requests_sent(cost);
        return true;
    }

}



