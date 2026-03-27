//
// Created by Mark on 3/27/26.
//


#include <gtest/gtest.h>
#include "../limiters/LeakyBucket.h"


TEST(TestLeakyBucket, basicTest) {
    LeakyBucket lb{3.0, 500};
    EXPECT_TRUE(lb.make_request(1,20));
    EXPECT_TRUE(lb.make_request(2,10));
    lb.shutdown_bucket();
}


TEST(TestLeakyBucket, afterShutdownFalse) {
    LeakyBucket lb{3.0, 500};
    EXPECT_TRUE(lb.make_request(1,20));
    EXPECT_TRUE(lb.make_request(2,10));
    lb.shutdown_bucket();
    EXPECT_FALSE(lb.make_request(3, 0));
}