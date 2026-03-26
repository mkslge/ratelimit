//
// Created by Mark on 3/26/26.
//
#include <gtest/gtest.h>
#include "../limiters/FixedWindow.h"
#include "../limiters/SlidingWindow.h"
#include <chrono>
#include <thread>
using namespace std::chrono_literals;





TEST(SlidingWindowTests, ZeroCapacityRejectsImmediately) {
    SlidingWindow sw(0, 1);

    EXPECT_FALSE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(42));
}

TEST(SlidingWindowTests, AcceptsUpToExactCapacity) {
    SlidingWindow sw(3, 1);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
}

TEST(SlidingWindowTests, DifferentClientsAreIndependent) {
    SlidingWindow sw(2, 1);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));

    EXPECT_TRUE(sw.make_request(2));
    EXPECT_TRUE(sw.make_request(2));
    EXPECT_FALSE(sw.make_request(2));
}

TEST(SlidingWindowTests, WeightedRequestsRespectCapacity) {
    SlidingWindow sw(5, 1);

    EXPECT_TRUE(sw.make_request(1, 2.0));
    EXPECT_TRUE(sw.make_request(1, 2.0));
    EXPECT_TRUE(sw.make_request(1, 1.0));
    EXPECT_FALSE(sw.make_request(1, 0.1));
}

TEST(SlidingWindowTests, RejectsRequestLargerThanTotalCapacity) {
    SlidingWindow sw(5, 1);

    EXPECT_FALSE(sw.make_request(1, 6.0));
    EXPECT_TRUE(sw.make_request(1, 5.0));
    EXPECT_FALSE(sw.make_request(1));
}

TEST(SlidingWindowTests, FractionalCostsWorkAtBoundary) {
    SlidingWindow sw(1, 1);

    EXPECT_TRUE(sw.make_request(1, 0.4));
    EXPECT_TRUE(sw.make_request(1, 0.6));
    EXPECT_FALSE(sw.make_request(1, 0.01));
}

TEST(SlidingWindowTests, CapacityRestoresAfterWindowExpires) {
    SlidingWindow sw(2, 1);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));

    std::this_thread::sleep_for(1100ms);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
}

TEST(SlidingWindowTests, OneClientsUsageDoesNotAffectAnotherAfterReset) {
    SlidingWindow sw(1, 1);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));

    EXPECT_TRUE(sw.make_request(2));
    EXPECT_FALSE(sw.make_request(2));

    std::this_thread::sleep_for(1100ms);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(2));
}

TEST(SlidingWindowTests, CostExactlyEqualToCapacitySucceeds) {
    SlidingWindow sw(10, 1);

    EXPECT_TRUE(sw.make_request(1, 10.0));
    EXPECT_FALSE(sw.make_request(1, 0.01));
}

TEST(SlidingWindowTests, RepeatedRejectionsDoNotCorruptState) {
    SlidingWindow sw(2, 1);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));

    std::this_thread::sleep_for(1100ms);

    EXPECT_TRUE(sw.make_request(1));
    EXPECT_TRUE(sw.make_request(1));
    EXPECT_FALSE(sw.make_request(1));
}