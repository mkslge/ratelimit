cmake_minimum_required(VERSION 3.31)
project(ratelimiter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS OFF)


include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)

#GOOGLE TEST SETUP ------------------------------------------

FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)



#LIBRARIES ------------------------------------------
add_library(RATE_LIMIT_CORE STATIC
        limiters/RateLimiter.cpp
        limiters/FixedWindow.cpp
        limiters/SlidingWindow.cpp
        limiters/TokenBucket.cpp
        limiters/LeakyBucket.cpp

)

#EXECUTABLES -------------------------------------------------

add_executable(ratelimiter main.cpp)
target_link_libraries(ratelimiter PRIVATE RATE_LIMIT_CORE)

add_executable(testFixedWindow tests/testFixedWindow.cpp)
target_link_libraries(testFixedWindow PRIVATE RATE_LIMIT_CORE gtest_main)

add_executable(testSlidingWindow tests/testSlidingWindow.cpp)
target_link_libraries(testSlidingWindow PRIVATE RATE_LIMIT_CORE gtest_main)

add_executable(testLeakyBucket tests/testLeakyBucket.cpp)
target_link_libraries(testLeakyBucket PRIVATE RATE_LIMIT_CORE gtest_main)


add_executable(allTests tests/tests.cpp)
target_link_libraries(allTests PRIVATE RATE_LIMIT_CORE gtest_main)


gtest_discover_tests(testFixedWindow)
gtest_discover_tests(testSlidingWindow)
gtest_discover_tests(testLeakyBucket)
gtest_discover_tests(allTests)

