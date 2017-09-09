#ifndef _LISTENER_H_
#define _LISTENER_H_

#include "Event.h"

class Event;

class Listener
{
    public:
        ~Listener();

        virtual void update(Event *e) = 0;

    protected:
        Listener();
};

#endif // _LISTENER_H_
