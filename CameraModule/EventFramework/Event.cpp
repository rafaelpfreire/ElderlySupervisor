#include "Event.h"

Event::Event()
{
}

Event::~Event()
{
}

void Event::subscribe(Listener *l)
{
    list.push_back(l);
}

void Event::remove(Listener *l)
{
}

void Event::notify()
{
    std::vector<Listener*>::iterator it;

    for(it = list.begin(); it != list.end(); ++it)
    {
        (*it)->update(this);
    }
}
