#include <iostream>
#include <chrono>

#ifndef SDIZOPROJECT_TIMER_H
#define SDIZOPROJECT_TIMER_H

using namespace std;
using namespace std::chrono;

class Timer {
public:
    high_resolution_clock::time_point beginningTime;
    high_resolution_clock::time_point finishingTime;

    void startTime();

    void stopTime();

    long long nanoMeasuredTime();


};


#endif //SDIZOPROJECT_TIMER_H