#pragma once

#include <mutex>
#include <iostream>

namespace graphcpp
{
    template<class SummableType>
    class MultiThreadSummator final
    {
    private:
        SummableType _sum;
        double _probability = 0;
        mutable std::mutex _add_mutex;
        
    public:
        explicit MultiThreadSummator(SummableType&& initial = SummableType());
        
        template<class SummableCompatibleType>
        void add(SummableCompatibleType&& addend, double probability);
        
        double current_probability() const;
        SummableType current_sum() const;
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
        //std::lock_guard lock(_add_mutex);

        _add_mutex.lock();
        
        addend *= probability;
        _sum += addend;
        _probability += probability;
        
        _add_mutex.unlock();
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
}
