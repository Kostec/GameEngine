#pragma once

template<class ...TParams>
class AbstractEventHandler
{
    using MyType = AbstractEventHandler<TParams...>;
public:
    virtual void call(TParams... params) = 0;

    virtual bool operator == (const MyType& handler) const
    {
        return isEquals(handler);
    }

    virtual bool operator != (const MyType& handler) const
    {
        return !(*this == handler);
    }

protected:
    AbstractEventHandler() {}
    virtual bool isEquals(const MyType& handler) const = 0;
};