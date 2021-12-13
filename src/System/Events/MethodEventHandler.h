#pragma once

#include "AbstractEventHandler.h"

template<class TObject, class ...TParams>
class MethodEventHandler : public AbstractEventHandler<TParams...>
{
    using TMethod = void(TObject::*)(TParams...);
    using MyType = MethodEventHandler;
public:
    MethodEventHandler(TObject& object, TMethod method) :
        AbstractEventHandler<TParams...>(),
        m_object(object),
        m_method(method)
    {
        assert(m_method != nullptr);
    }
    virtual void call(TParams... params) override final
    {
        (m_object.*m_method)(params...);
    }

private:
    TObject& m_object;
    TMethod m_method;

protected:
    virtual bool isEquals(const AbstractEventHandler<TParams...>& handler) const override
    {
        const MyType* _handler = dynamic_cast<const MyType*>(&handler);
        return ( (_handler != nullptr) && (&m_object == &_handler->m_object) && (m_method == _handler->m_method) );
    }
};
