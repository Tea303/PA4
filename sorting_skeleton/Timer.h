#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer {
public:
    void start() {
        start_ = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        end_ = std::chrono::high_resolution_clock::now();
    }

    // Returns elapsed time in milliseconds
    double elapsedMilliseconds() const {
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
            end_ - start_);
        return duration.count() / 1000.0;
    }

private:
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point end_;
};

#endif // TIMER_H
