#ifndef _EVENT_H_
#define _EVENT_H_

#include <algorithm>
#include <vector>
#include <memory>
#include "Handler.h"

template<class Type> class Event
{
    using HandlerPtr = std::shared_ptr<Handler< Type > >;

    public:
        Event(){}
        ~Event(){}

        void subscribe(HandlerPtr h)
        {
            list.push_back(h);
        }

        void remove(HandlerPtr h)
        {
            list.erase(std::remove(list.begin(), list.end(), h), list.end());
        }

        void emit(Type value)
        {
            typename std::vector<HandlerPtr>::iterator it;
            
            for(it = list.begin(); it != list.end(); ++it)
            {
                (*it)->handle(value);
            }
        }

    protected:
        std::vector<HandlerPtr> list;
};

#endif // _EVENT_H_
