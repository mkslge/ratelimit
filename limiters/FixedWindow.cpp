//
// Created by Mark on 3/24/26.
//

#include "FixedWindow.h"


bool FixedWindow::make_request(ID id) {
   return FixedWindow::make_request(id, 1.0);
}


bool FixedWindow::make_request(ID id, double cost) {
    long double curr_window_ = gen_window();
    if (!clients.contains(id) || clients[id].get()->curr_window != curr_window_) {
        //still needs to subtract cost
        clients[id] = std::make_unique<ClientInfo>(ClientInfo{id, 0, curr_window_});

    }
    double requests_sent = clients[id].get()->requests;
    if (requests_sent + cost > rate_per_second_) {
        return false;
    } else {
        requests_sent += cost;
        return true;
    }

}


long double FixedWindow::gen_window() const {
    auto now = std::chrono::system_clock::now();
    auto epoch_dur = now.time_since_epoch();
    auto time = std::chrono::duration_cast<std::chrono::seconds>(epoch_dur).count();
    return std::fmod(time, window_length_);
}
