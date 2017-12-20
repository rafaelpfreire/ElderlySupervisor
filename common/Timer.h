#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>

class Timer
{
    public:
        Timer();
        ~Timer();

        void start();
        void restart();
        double ellapsed();

    protected:
        std::chrono::steady_clock::time_point start_time;
};

#endif //_TIMER_H_
