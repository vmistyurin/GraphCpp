#pragma once

#include <condition_variable>
#include <mutex>
#include <future>

#include "core/utils.hpp"

namespace graphcpp
{
    template<class SummableType>
    class MultiThreadSummator final
    {
    private:
        SummableType _sum;
        double _probability = 0;
        mutable std::mutex _add_mutex;
        std::promise<SummableType> _result = std::promise<SummableType>();
        
    public:
        explicit MultiThreadSummator(SummableType&& initial);
        
        template<class SummableCompatibleType>
        void add(SummableCompatibleType&& addend, double probability);
        
        double current_probability() const;
        SummableType current_sum() const;

        std::future<SummableType> start_compute();
    };
    
    template<class SummableType>
    MultiThreadSummator<SummableType>::MultiThreadSummator(SummableType&& initial) :
        _sum(std::move(initial))
    {
    }
    
    template<class SummableType>
    template<class SummableCompatibleType>
    void MultiThreadSummator<SummableType>::add(SummableCompatibleType&& addend, double probability)
    {
        std::lock_guard lock(_add_mutex);

        addend *= probability;
        _sum += addend;
        _probability += probability;
        
        if (are_doubles_equal(_probability, 1))
        {
            _result.set_value(_sum);
        }
    }
    
    template<class SummableType>
    double MultiThreadSummator<SummableType>::current_probability() const
    {
        return _probability;
    }
    
    template<class SummableType>
    SummableType MultiThreadSummator<SummableType>::current_sum() const
    {
        return _sum;
    }
    
    template<class SummableType>
    std::future<SummableType> MultiThreadSummator<SummableType>::start_compute()
    {
        return _result.get_future();
    }
}
