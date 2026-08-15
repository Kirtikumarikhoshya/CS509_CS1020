#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
    }

    double getElapsedMilliseconds() const {
        std::chrono::duration<double, std::milli> duration = end_time - start_time;
        return duration.count();
    }
};

#endif // TIMER_HPP