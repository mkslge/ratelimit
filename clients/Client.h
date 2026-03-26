//
// Created by Mark on 3/24/26.
//

#ifndef CLIENTINFO_H
#define CLIENTINFO_H


class Client {
protected:
    int id_;
    double requests_sent_;
public:
    explicit Client(int id) : id_(id), requests_sent_(0) {

    };
    int get_id() const {
        return id_;
    }

    double get_requests_sent() {
        return requests_sent_;
    }

    void add_requests_sent(double requests) {
        requests_sent_ += requests;
    }
    virtual ~Client() = default;
};



#endif //CLIENTINFO_H
