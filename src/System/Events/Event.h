#pragma once

#include <list>
#include "MethodEventHandler.h"

template<class ...TParams>
class Event
{
    using TEventHandler = AbstractEventHandler<TParams...>;
    using TEventHandlerIt = typename std::list<TEventHandler*>::const_iterator;
public:
    Event() :
        m_handlers()
    {
    }

    ~Event()
    {
        for (TEventHandler* oneHandler : m_handlers)
            delete oneHandler;
        m_handlers.clear();
    }

    void operator()(TParams... params)
    {
        for (TEventHandler* oneHandler : m_handlers)
            oneHandler->call(params...);
    }

    void operator+=(TEventHandler& eventHandler)
    {
        if (findEventHandler(eventHandler) == m_handlers.end())
        {
            m_handlers.push_back(&eventHandler);
        }
    }

    void operator-=(TEventHandler& eventHandler)
    {
        auto it = findEventHandler(eventHandler);
        if (it != m_handlers.end())
        {
            TEventHandler* removedEventHandler = *it;
            m_handlers.erase(it);
            delete removedEventHandler;
        }
    }

private:
    std::list<TEventHandler*> m_handlers;

    inline TEventHandlerIt findEventHandler(TEventHandler& eventHandler) const
    {
        return std::find_if(m_handlers.cbegin(), m_handlers.cend(), [&eventHandler](const TEventHandler* oneHandler)
            {
                return (*oneHandler == eventHandler);
            });
    }
};

template<class TObject, class ...TParams>
AbstractEventHandler<TParams...>& createMethodEventHandler(TObject& object, void(TObject::* method)(TParams...))
{
    return *new MethodEventHandler<TObject, TParams...>(object, method);
}

#define METHOD_HANDLER( Object, Method ) createMethodEventHandler( Object, &Method )
#define MY_METHOD_HANDLER( Method ) METHOD_HANDLER( *this, Method )