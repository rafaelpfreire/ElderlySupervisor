#ifndef _HANDLER_H_
#define _HANDLER_H_

#include <functional>

template<class Type> class Handler
{

    public:
        Handler(std::function<void(Type)> f): h(f){}
        ~Handler(){}

        void handle(Type val)
        {
            h(val);
        }

    protected:
        std::function<void(Type)> h;
};

#endif //_HANDLER_H_
