#ifndef _EVENT_H_
#define _EVENT_H_

//#include <vector>
//#include "Listener.h"

//class Listener;
//
//class Event
//{
//    public:
//        ~Event();
//
//        void subscribe(Listener *l);
//        void remove(Listener *l);
//        void notify();
//
//    protected:
//        Event();
//
//        std::vector<Listener*> list;
//
//};

#include <functional>
#include <algorithm>
#include <vector>

template<class Type> class Event
{
    public:
        //Event();
        //~Event();

        //void subscribe(std::function<void(Type)> f);
        //void remove(std::function<void(Type)> f);
        //void emit(Type value);
        Event()
        {
        }
        ~Event()
        {
        }
        void subscribe(std::function<void(Type)> f)
        {
            list.push_back(f);
        }
        void remove(std::function<void(Type)> f)
        {
            list.erase(std::remove(list.begin(), list.end(), f), list.end());
        }
        void emit(Type value)
        {
            typename std::vector<std::function< void(Type) > >::iterator it;
            
            for(it = list.begin(); it != list.end(); ++it)
            {
                (*it)(value);
            }
        }

    protected:
        std::vector<std::function< void(Type) > > list;
};

#endif // _EVENT_H_
