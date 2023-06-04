#include "Timer.h"


void Timer::startTime() {
    beginningTime = high_resolution_clock::now();
}

void Timer::stopTime() {
    finishingTime = high_resolution_clock::now();
}

long long  Timer::nanoMeasuredTime() {
    return duration_cast<nanoseconds>(Timer::finishingTime - Timer::beginningTime).count();
}

