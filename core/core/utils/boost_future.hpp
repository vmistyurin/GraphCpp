#pragma once

#include <functional>

#define BOOST_THREAD_VERSION 4
#include "boost/thread.hpp"

namespace graphcpp
{
    template<class T>
    boost::future<T> combine_futures(
        boost::future<T>&& first_future,
        boost::future<T>&& second_future,
        std::function<T(T&&, T&&)> combiner
    )
    {
        return first_future
            .then([second_future = std::move(second_future), combiner = std::move(combiner)](boost::future<T> first_future) mutable
            {
                auto second_result = second_future.get();
                auto first_result = first_future.get();
                
                return combiner(std::move(first_result), std::move(second_result));
            });
    }
}
