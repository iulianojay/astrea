#pragma once

#include <chrono>

class Time {
public:
    Time();
    ~Time();

private:

    std::chrono::duration<double> time;
};