cmake_minimum_required(VERSION 3.31)
project(ratelimter)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

enable_testing()



add_executable(allTests tests/tests.cpp)
target_link_libraries(allTests PUBLIC gtest_main)

include(GoogleTest)
gtest_discover_tests(allTests)

add_executable(ratelimiter main.cpp
        limiters/RateLimiter.cpp
        limiters/RateLimiter.h
        ClientInfo.h
        limiters/FixedWindow.cpp
        limiters/FixedWindow.h
        limiters/SlidingWindow.cpp
        limiters/SlidingWindow.h
        limiters/TokenBucket.cpp
        limiters/TokenBucket.h)

add_executable(testFixedWindow tests/testfixedwindow.cpp
                limiters/RateLimiter.cpp limiters/FixedWindow.cpp

)