#pragma once

#include <algorithm>

template<class IteratorType>
class FirstNRange
{
private:
    IteratorType _begin;
    IteratorType _end;
public:

    FirstNRange(IteratorType begin, size_t N) :
        _begin(begin), _end(std::next(begin, N))
    {
    }

    IteratorType begin() const
    {
        return _begin;
    }

    IteratorType end() const
    {
        return _end;
    }
};