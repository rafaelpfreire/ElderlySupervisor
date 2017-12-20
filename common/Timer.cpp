#include "Timer.h"


using namespace std::chrono;

Timer::Timer()
{
    start();
}

Timer::~Timer()
{
}

void Timer::start()
{
    start_time = steady_clock::now();
}

void Timer::restart()
{
    start();
}

double Timer::ellapsed()
{
    duration<double, std::ratio<1, 1000>> duration_ms = steady_clock::now() - start_time;

    return double(duration_ms.count());
}

