//
// Created by Mark on 3/26/26.
//

#ifndef FIXEDWINDOWCLIENT_H
#define FIXEDWINDOWCLIENT_H

#include "Client.h"

class FixedWindowClient : public Client {
private:
    long long curr_window_;
public:
    FixedWindowClient(int id, long long curr_window) : Client(id),
    curr_window_(curr_window) {

    }

    long long get_curr_window() const {
        return curr_window_;
    }
};



#endif //FIXEDWINDOWCLIENT_H
