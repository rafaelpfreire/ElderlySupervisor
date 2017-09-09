#ifndef _EVENT_H_
#define _EVENT_H_

#include <vector>
#include "Listener.h"

class Listener;

class Event
{
    public:
        ~Event();

        void subscribe(Listener *l);
        void remove(Listener *l);
        void notify();

    protected:
        Event();

        std::vector<Listener*> list;

};

#endif // _EVENT_H_
