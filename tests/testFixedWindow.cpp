//
// Created by Mark on 3/25/26.
//
#include <gtest/gtest.h>
#include "../limiters/FixedWindow.h"


TEST(FixedWindowTests, testBasicAlwaysFalse) {
    FixedWindow fw(0,1);

    for (int i =0 ; i < 500;i++) {
        EXPECT_FALSE(fw.make_request(1));
    }
}

TEST(FixedWindowTests, testBasicAlwaysTrue) {
    FixedWindow fw{1,1};
    for (int i = 0; i < 500;i++) {
        EXPECT_TRUE(fw.make_request(i));
    }

}

TEST(FixedWindowTests, testOverflow) {
    FixedWindow fw{1,1};
    bool one_request_failed = false;
    for (int i = 0; i < 4;i++) {
        if (!fw.make_request(1)) {
            one_request_failed = true;
        }
    }
    EXPECT_TRUE(one_request_failed);
}

TEST(FixedWindowTests, onlyNewIDs) {
    FixedWindow fw{1,1};
    for (int i = 0; i < 1000;i++) {
        EXPECT_TRUE(fw.make_request(i));
    }
}